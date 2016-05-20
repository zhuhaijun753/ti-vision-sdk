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
 *  \file bsp_boardTda3xxMultiDes.h
 *
 *  \brief TDA3XX Multi Deserialiser board data.
 *  In Multi deserializer board the camera inputs connects are shown below
 *   CAM1 ---> VIN1A
 *   CAM2 ---> VIN1B
 *   CAM3 ---> VIN2A
 *   CAM4 ---> VIN2B
 *   CAM5 ---> NA
 *   CAM6 ---> NA
 */

#ifndef BSP_BOARD_TDA3XX_MULTIDES_H_
#define BSP_BOARD_TDA3XX_MULTIDES_H_

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

/*
 * Cameras(OVSENSOR) addresses
 * These adresses are "Match" addresses used for addressing target camera at
 * deserializer's side.
 * The real camera address "CAMERA_ID_ADDR"is 0x30 (0x60/2) and it is the same
 * for all cameras
 * !!!IMPORTANT!!! If redifining camera addresses they always have to be put
 * into consecutive order
 * (0x20 - CAMERA 1, 0x21 - CAMERA 2, 0x22 - CAMERA 3 etc.).
 * The following is not allowed: 0x20 - CAMERA 1, 0x22 - CAMERA 2, 0x21 - CAMERA
 * 3 etc.
 * These alias address should be in sync with what is defined in bsputils_app.c
 * file.
 */
#define BOARD_OV1063x_1_ALIAS_I2C_ADDR     (0x38U) /* 0x70/2 */
#define BOARD_OV1063x_2_ALIAS_I2C_ADDR     (0x39U) /* 0x72/2 */
#define BOARD_OV1063x_3_ALIAS_I2C_ADDR     (0x3AU) /* 0x74/2 */
#define BOARD_OV1063x_4_ALIAS_I2C_ADDR     (0x3BU) /* 0x76/2 */
#define BOARD_OV1063x_5_ALIAS_I2C_ADDR     (0x3CU) /* 0x78/2 */
#define BOARD_OV1063x_6_ALIAS_I2C_ADDR     (0x3DU) /* 0x7A/2 */

#ifdef VPS_VIP_BUILD

#define VPS_CAPT_DRV_ID_TDA3XX_MULTIDES_OV1063X     (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_1_TDA3XX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_2_TDA3XX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB))
#define VPS_CAPT_DRV_INST_ID_3_TDA3XX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_4_TDA3XX_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB))

#else

#define VPS_CAPT_DRV_ID_TDA3XX_MULTIDES_OV1063X         (0U)

#define VPS_CAPT_DRV_INST_ID_1_TDA3XX_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_2_TDA3XX_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_3_TDA3XX_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_4_TDA3XX_MULTIDES_OV1063X  (0U)
#endif

#define BSP_BOARD_TDA3XX_MULTIDES_DEVDATA                                    \
    {                                                                        \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_1,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_1,                       /* i2cInstId */  \
            BOARD_OV1063x_1_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA3XX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_1_TDA3XX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                   /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_1,                       /* i2cInstId */  \
            BOARD_OV1063x_2_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA3XX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_2_TDA3XX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                   /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_3,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_1,                       /* i2cInstId */  \
            BOARD_OV1063x_3_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA3XX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_3_TDA3XX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                   /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,            /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_4,            /* instId */     \
            BSP_DEVICE_I2C_INST_ID_1,                       /* i2cInstId */  \
            BOARD_OV1063x_4_ALIAS_I2C_ADDR,                 /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA3XX_MULTIDES_OV1063X,        /* drvId */      \
            VPS_CAPT_DRV_INST_ID_4_TDA3XX_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda3xx,                   /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda3xx,                  /* powerOnDev */ \
        },                                                                   \
    }

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_BOARD_TDA3XX_MULTIDES_H_ */

/* @} */
