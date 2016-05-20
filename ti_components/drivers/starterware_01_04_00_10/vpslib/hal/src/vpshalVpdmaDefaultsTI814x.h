/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 * \file vpshalVpdmaDefaultsTI814x.h
 *
 * \brief VPS VPDMA HAL default configuration file
 * This file contains default configuration for VPDMA.
 *
 */

#ifndef VPSSHALVPDMADEFAULTS_TI814X_H_
#define VPSSHALVPDMADEFAULTS_TI814X_H_

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
        {VPSHAL_VPDMA_CHANNEL_PRI_LUMA,                                       \
         VPDMA_PRI_LUMA_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_PRI_CHROMA,                                     \
         VPDMA_PRI_CHROMA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_PRI_FLD1_LUMA,                                  \
         VPDMA_PRI_FLD1_LUMA_CSTAT,                                           \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_PRI_FLD1_CHROMA,                                \
         VPDMA_PRI_FLD1_CHROMA_CSTAT,                                         \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_PRI_FLD2_LUMA,                                  \
         VPDMA_PRI_FLD2_LUMA_CSTAT,                                           \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_PRI_FLD2_CHROMA,                                \
         VPDMA_PRI_FLD2_CHROMA_CSTAT,                                         \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_PRI_MV0,                                        \
         VPDMA_PRI_MV0_CSTAT,                                                 \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_PRI_MV_OUT,                                     \
         VPDMA_PRI_MV_OUT_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_WB0,                                            \
         VPDMA_WB0_CSTAT,                                                     \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_AUX_LUMA,                                       \
         VPDMA_AUX_LUMA_CSTAT,                                                \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_AUX_CHROMA,                                     \
         VPDMA_AUX_CHROMA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_WB1,                                            \
         VPDMA_WB1_CSTAT,                                                     \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_GRPX0,                                          \
         VPDMA_GRPX0_DATA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_GRPX1,                                          \
         VPDMA_GRPX1_DATA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_GRPX2,                                          \
         VPDMA_GRPX2_DATA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_STENCIL0,                                       \
         VPDMA_STENCIL0_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_STENCIL1,                                       \
         VPDMA_STENCIL1_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_STENCIL2,                                       \
         VPDMA_STENCIL2_CSTAT,                                                \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_CLUT0,                                          \
         VPDMA_GRPX0_DATA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_CLUT1,                                          \
         VPDMA_GRPX1_DATA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_CLUT2,                                          \
         VPDMA_GRPX2_DATA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
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
        {VPSHAL_VPDMA_CHANNEL_NF_RD,                                          \
         VPDMA_NF_RD_CSTAT,                                                   \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_NF_WR_LUMA,                                     \
         VPDMA_NF_WR_LUMA_CSTAT,                                              \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_NF_WR_CHROMA,                                   \
         VPDMA_NF_WR_CHROMA_CSTAT,                                            \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_NF_PREV_LUMA,                                   \
         VPDMA_NF_PREV_LUMA_CSTAT,                                            \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_NF_PREV_CHROMA,                                 \
         VPDMA_NF_PREV_CHROMA_CSTAT,                                          \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_INVALID, NULL, VPSHAL_VPDMA_MT_NONTILEDMEM, 0}, \
        {VPSHAL_VPDMA_CHANNEL_VBI_SD,                                         \
         VPDMA_VBI_SDVENC_CSTAT,                                              \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_WB2,                                            \
         VPDMA_WB2_CSTAT,                                                     \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_BP0,                                            \
         VPDMA_BP0_CSTAT,                                                     \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_BP1,                                            \
         VPDMA_BP1_CSTAT,                                                     \
         VPSHAL_VPDMA_MT_NONTILEDMEM, 0},                                     \
        {VPSHAL_VPDMA_CHANNEL_SEC0_LUMA,                                      \
         VPDMA_SEC0_LUMA_CSTAT,                                               \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_SEC0_CHROMA,                                    \
         VPDMA_SEC0_CHROMA_CSTAT,                                             \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_SEC1_LUMA,                                      \
         VPDMA_SEC1_LUMA_CSTAT,                                               \
         VPSHAL_VPDMA_MT_TILEDMEM, 0},                                        \
        {VPSHAL_VPDMA_CHANNEL_SEC1_CHROMA,                                    \
         VPDMA_SEC1_CHROMA_CSTAT,                                             \
         VPSHAL_VPDMA_MT_TILEDMEM, 0}                                         \
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

#endif /* #ifndef VPSSHALVPDMADEFAULTS_TI814X_H_ */
