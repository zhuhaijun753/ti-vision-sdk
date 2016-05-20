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
 *  \file ar0140_1280x720_60fps_Linear.h
 *
 *  \brief AR0140 sensor linear mode Setting file.
 *
 */

#ifndef BSPDRV_AR0140_1280X720_60FPS_LINEAR_H_
#define BSPDRV_AR0140_1280X720_60FPS_LINEAR_H_

/******************[1280x720 60fps Linear]******************/
    /* Linear Mode Setup */
#define BSP_AR0140SENSORS_LINEAR \
{ \
    {0x301A, 0x10D8, 0xff},     /* RESET_REGISTER        */ \
    {BSP_VID_SENSOR_DLY_REG, BSP_AR0140_SENSOR_DLY_IN_MS_AFTER_RESET, \
        BSP_VID_SENSOR_DLY_REG_MASK},/* Dummy register to pu Delay */ \
    {0x3082, 0x0009, 0x00},     /* OPERATION_MODE_CTRL   */ \
    {0x318C, 0x0000, 0x00},     /* HDR_MC_CTRL2          */ \
    {0x3200, 0x0000, 0x00},     /* ADACD_CONTROL         */ \
    {0x31D0, 0x0000, 0x00},     /* COMPANDING            */ \
    {0x30B0, 0x0000, 0x00},     /* DIGITAL_TEST          */ \
    {0x30BA, 0x012C, 0x00},     /* DIGITAL_CTRL          */ \
    {0x31AC, 0x0C0C, 0x00},     /* DATA_FORMAT_BITS      */ \
    {0x31AE, 0x0301, 0x00},     /* SERIAL_FORMAT         */ \
    {0x301A, 0x10DC, 0xFF},     /* RESET_REGISTER        */ \
}

#endif /* #ifndef BSPDRV_AR0140_1280X720_60FPS_LINEAR_H_  */

