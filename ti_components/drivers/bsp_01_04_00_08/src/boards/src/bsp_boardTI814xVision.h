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
 *  \file bsp_boardTI814xVision.h
 *
 *  \brief TI814x Vision board data.
 */

#ifndef BSP_BOARD_TI814X_VISION_H_
#define BSP_BOARD_TI814X_VISION_H_

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

#ifdef VPS_VIP_BUILD

#define VPS_CAPT_DRV_ID_TI814X_VISION_MT9V022       (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TI814X_VISION_TVP5158       (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TI814X_VISION_OV1063X       (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TI814X_VISION_MT9V022 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TI814X_VISION_TVP5158 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TI814X_VISION_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TI814X_VISION_MT9V022       (0U)
#define VPS_CAPT_DRV_ID_TI814X_VISION_TVP5158       (0U)
#define VPS_CAPT_DRV_ID_TI814X_VISION_OV1063X       (0U)

#define VPS_CAPT_DRV_INST_ID_TI814X_VISION_MT9V022  (0U)
#define VPS_CAPT_DRV_INST_ID_TI814X_VISION_TVP5158  (0U)
#define VPS_CAPT_DRV_INST_ID_TI814X_VISION_OV1063X  (0U)

#endif

#define BSP_BOARD_TI814X_VISION_DEVDATA                                  \
    {                                                                    \
        {                                                                \
            FVID2_VID_SENSOR_MT9V022_DRV,               /* devDrvId */   \
            0U,                                         /* instId */     \
            BSP_DEVICE_I2C_INST_ID_2,                   /* i2cInstId */  \
            BOARD_MT9V022_I2C_ADDR_0,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TI814X_VISION_MT9V022,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TI814X_VISION_MT9V022, /* drvInstId */  \
            &Bsp_boardSelectDeviceTI814xVisionTI81xx,   /* selectDev */  \
            NULL,                                       /* resetDev */   \
            NULL,                                       /* powerOnDev */ \
        },                                                               \
        {                                                                \
            FVID2_VID_DEC_TVP5158_DRV,                  /* devDrvId */   \
            0U,                                         /* instId */     \
            BSP_DEVICE_I2C_INST_ID_2,                   /* i2cInstId */  \
            BOARD_TVP5158_I2C_ADDR_7,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TI814X_VISION_TVP5158,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TI814X_VISION_TVP5158, /* drvInstId */  \
            &Bsp_boardSelectDeviceTI814xVisionTI81xx,   /* selectDev */  \
            NULL,                                       /* resetDev */   \
            NULL,                                       /* powerOnDev */ \
        },                                                               \
        {                                                                \
            FVID2_VID_SENSOR_OV1063X_DRV,               /* devDrvId */   \
            0U,                                         /* instId */     \
            BSP_DEVICE_I2C_INST_ID_2,                   /* i2cInstId */  \
            BOARD_OV1063x_I2C_ADDR_0,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TI814X_VISION_OV1063X,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TI814X_VISION_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTI814xVisionTI81xx,   /* selectDev */  \
            NULL,                                       /* resetDev */   \
            NULL,                                       /* powerOnDev */ \
        }                                                                \
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

#endif  /* #ifndef BSP_BOARD_TI814X_VISION_H_ */

/* @} */
