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
 *  \file bsp_boardTda2xxMultiDes.h
 *
 *  \brief TDA2XX Monster Cam board data.
 *   In Monster Cam board the camera inputs connects are shown below
 *   RADAR                  ---> VIN1A
 *   DM388                  ---> VIN2A
 *   FPD link2              ---> VIN3A
 *   Not connected          ---> VIN4A
 *   Stereo / FPD link 1    ---> VIN5A
 *   Stereo / FPD link 3    ---> VIN6A
 */

#ifndef BSP_BOARD_TDA2XX_MONSTERCAM_H_
#define BSP_BOARD_TDA2XX_MONSTERCAM_H_

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
#define BOARD_OV1063x_1_ALIAS_I2C_ADDR      (0x38U) /* 0x70/2 */
#define BOARD_OV1063x_2_ALIAS_I2C_ADDR      (0x39U) /* 0x72/2 */
#define BOARD_OV1063x_3_ALIAS_I2C_ADDR      (0x3AU) /* 0x72/2 */

#ifdef VPS_VIP_BUILD

#define VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_APT_AR0132   (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA2XX_INST_0_APT_AR0132 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2XX_INST_1_APT_AR0132 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA))

#define VPS_CAPT_DRV_ID_TDA2XX_MULTIDES_OV1063X     (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_1_TDA2XX_FPD_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_2_TDA2XX_FPD_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_3_TDA2XX_FPD_MULTIDES_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_APT_AR0132           (0U)

#define VPS_CAPT_DRV_INST_ID_TDA2XX_INST_0_APT_AR0132       (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_INST_1_APT_AR0132       (0U)

#define VPS_CAPT_DRV_ID_TDA2XX_MULTIDES_OV1063X             (0U)

#define VPS_CAPT_DRV_INST_ID_1_TDA2XX_FPD_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_2_TDA2XX_FPD_MULTIDES_OV1063X  (0U)
#define VPS_CAPT_DRV_INST_ID_3_TDA2XX_FPD_MULTIDES_OV1063X  (0U)

#endif

#define BSP_BOARD_TDA2XX_MONSTERCAM_DEVDATA                                      \
    {                                                                            \
        {                                                                        \
            FVID2_VID_SENSOR_APT_AR0132RCCC_DRV,            /* devDrvId */       \
            BSP_DEVICE_APT_AR0132_INST_ID_0,                /* instId */         \
            BSP_DEVICE_I2C_INST_ID_2,                       /* i2cInstId */      \
            BOARD_APT_AR0132RCCC_I2C_ADDR_0,                /* i2cAddr */        \
            VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_APT_AR0132,      /* drvId */          \
            VPS_CAPT_DRV_INST_ID_TDA2XX_INST_0_APT_AR0132,  /* drvInstId */      \
            &Bsp_boardSelectDeviceTda2xxMonsterCam,         /* selectDev */      \
            NULL,                                           /* resetDev */       \
            &Bsp_boardPowerOnDeviceTda2xx,                  /* powerOnDev */     \
        },                                                                       \
        {                                                                        \
            FVID2_VID_SENSOR_APT_AR0132RCCC_DRV,            /* devDrvId */       \
            BSP_DEVICE_APT_AR0132_INST_ID_0,                /* instId */         \
            BSP_DEVICE_I2C_INST_ID_2,                       /* i2cInstId */      \
            BOARD_APT_AR0132RCCC_I2C_ADDR_1,                /* i2cAddr */        \
            VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_APT_AR0132,      /* drvId */          \
            VPS_CAPT_DRV_INST_ID_TDA2XX_INST_1_APT_AR0132,  /* drvInstId */      \
            NULL,                                           /* selectDev */      \
            NULL,                                           /* resetDev */       \
            &Bsp_boardPowerOnDeviceTda2xx,                  /* powerOnDev */     \
        },                                                                       \
        {                                                                        \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,                /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_1,                /* instId */     \
            BSP_DEVICE_I2C_INST_ID_2,                           /* i2cInstId */  \
            BOARD_OV1063x_1_ALIAS_I2C_ADDR,                     /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_MULTIDES_OV1063X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_1_TDA2XX_FPD_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxMonsterCam,             /* selectDev */  \
            NULL,                                               /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                      /* powerOnDev */ \
        },                                                                       \
        {                                                                        \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,                /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_2,                /* instId */     \
            BSP_DEVICE_I2C_INST_ID_2,                           /* i2cInstId */  \
            BOARD_OV1063x_2_ALIAS_I2C_ADDR,                     /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_MULTIDES_OV1063X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_2_TDA2XX_FPD_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxMonsterCam,             /* selectDev */  \
            NULL,                                               /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                      /* powerOnDev */ \
        },                                                                       \
        {                                                                        \
            FVID2_VID_SENSOR_MULDES_OV1063X_DRV,                /* devDrvId */   \
            BSP_DEVICE_MULDES_OV1063X_INST_ID_3,                /* instId */     \
            BSP_DEVICE_I2C_INST_ID_2,                           /* i2cInstId */  \
            BOARD_OV1063x_3_ALIAS_I2C_ADDR,                     /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_MULTIDES_OV1063X,            /* drvId */      \
            VPS_CAPT_DRV_INST_ID_3_TDA2XX_FPD_MULTIDES_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xxMonsterCam,             /* selectDev */  \
            NULL,                                               /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                      /* powerOnDev */ \
        }                                                                        \
                                                                                 \
    }                                                                            \

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

#endif  /* #ifndef BSP_BOARD_TDA2XX_MONSTERCAM_H_ */

/* @} */
