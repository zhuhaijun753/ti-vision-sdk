/******************************************************************************
 *                                                                            *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bspdrv_ar0140_tida00262_1280x800_30fps_wdr.h
 *
 *  \brief TIDA00262 has a restriction on the pixel clock. This configuration
 *          ensures the pixel clock is as required. Other WDR configurations
 *          are common.
 *
 */

#ifndef BSPDRV_AR0140_TIDA00262_1280x800_30FPS_WDR_H_
#define BSPDRV_AR0140_TIDA00262_1280x800_30FPS_WDR_H_

/******************[1280x720 60fps Linear]******************/
    /* Linear Mode Setup */
#define BSP_AR0140_TIDA00262_SENSORS_WDR \
{ \
    {0x301A, 0x10D8, 0xff},     /* RESET_REGISTER       */ \
    {BSP_VID_SENSOR_DLY_REG, BSP_AR0140_SENSOR_DLY_IN_MS_AFTER_RESET, \
        BSP_VID_SENSOR_DLY_REG_MASK}, /* Dummy register to pu Delay */ \
    /* PLL_configuration_Parallel */ \
    {0x302A, 0x0006, 0x00},     /* VT_PIX_CLK_DIV       */ \
    {0x302C, 0x0001, 0x00},     /* VT_SYS_CLK_DIV       */ \
    {0x302E, 0x0004, 0x00},     /* PRE_PLL_CLK_DIV      */ \
    {0x3030, 0x0048, 0x00},     /* PLL_MULTIPLIER       */ \
    {0x3036, 0x000C, 0x00},     /* OP_PIX_CLK_DIV       */ \
    {0x3038, 0x0001, 0x00},     /* OP_SYS_CLK_DIV       */ \
 \
    /* 1280x800 30fps_configuration */ \
    {0x3004, 0x0020, 0x00},     /* X_ADDR_START             */ \
    {0x3002, 0x0018, 0x00},     /* Y_ADDR_START             */ \
    {0x3008, 0x051F, 0x00},     /* X_ADDR_END               */ \
    {0x3006, 0x0337, 0x00},     /* Y_ADDR_END               */ \
    {0x300A, 0x05AE, 0x00},     /* FRAME_LENGTH_LINES       */ \
    {0x300C, 0x0672, 0x00},     /* LINE_LENGTH_PCK          */ \
    {0x3012, 0x0200, 0x00},     /* COARSE_INTEGRATION_TIME  */ \
    {0x301A, 0x10DC, 0xFF},     /* RESET_REGISTER        */    \
}

#endif /* #ifndef BSPDRV_AR0140_TIDA00262_1280x800_30FPS_WDR_H_  */

