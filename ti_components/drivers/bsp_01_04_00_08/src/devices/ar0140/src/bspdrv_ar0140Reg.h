/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bspdrv_ar0140_Reg.h
 *
 *  \brief AR0140 sensor Register file.
 *
 */

#ifndef BSPDRV_AR0140_REG_H_
#define BSPDRV_AR0140_REG_H_

#define BSP_AR0140SENSORS_CFG_1280x720 \
{ \
    {0x301A, 0x10D8, 0x00},     /* RESET_REGISTER           */ \
    {0x3004, 0x0012, 0x00},     /* X_ADDR_START             */ \
    {0x3002, 0x0040, 0x00},     /* Y_ADDR_START             */ \
    {0x3008, 0x0519, 0x00},     /* X_ADDR_END               */ \
    {0x3006, 0x0317, 0x00},     /* Y_ADDR_END               */ \
    {0x300A, 0x02EE, 0x00},     /* FRAME_LENGTH_LINES       */ \
    {0x300C, 0x0672, 0x00},     /* LINE_LENGTH_PCK          */ \
    {0x3012, 0x002D, 0x00},     /* COARSE_INTEGRATION_TIME  */ \
    {0x30A2, 0x0001, 0x00},     /* X_ODD_INC                */ \
    {0x30A6, 0x0001, 0x00},     /* Y_ODD_INC                */ \
    {0x3040, 0x0000, 0x00},     /* READ_MODE                */ \
    {0x3064, 0x1802, 0x00},     /* SMIA_TEST                */ \
    {0x301A, 0x10DC, 0x00},     /* RESET_REGISTER           */ \
}

#define BSP_AR0140SENSORS_CFG_1280x800 \
{ \
    {0x301A, 0x10D8, 0x00},     /* RESET_REGISTER           */ \
    {0x3004, 0x0020, 0x00},     /* X_ADDR_START             */ \
    {0x3002, 0x0018, 0x00},     /* Y_ADDR_START             */ \
    {0x3008, 0x051F, 0x00},     /* X_ADDR_END               */ \
    {0x3006, 0x0337, 0x00},     /* Y_ADDR_END               */ \
    {0x300A, 0x05DC, 0x00},     /* FRAME_LENGTH_LINES       */ \
    {0x300C, 0x0672, 0x00},     /* LINE_LENGTH_PCK          */ \
    {0x3012, 0x002D, 0x00},     /* COARSE_INTEGRATION_TIME  */ \
    {0x30A2, 0x0001, 0x00},     /* X_ODD_INC                */ \
    {0x30A6, 0x0001, 0x00},     /* Y_ODD_INC                */ \
    {0x3040, 0x0000, 0x00},     /* READ_MODE                */ \
    {0x3064, 0x1802, 0x00},     /* SMIA_TEST                */ \
    {0x301A, 0x10DC, 0x00},     /* RESET_REGISTER        */ \
}

#endif /* #ifndef BSPDRV_AR0140_REG_H_  */

