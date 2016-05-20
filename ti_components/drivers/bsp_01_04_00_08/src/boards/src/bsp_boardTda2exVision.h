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
 *  \file bsp_boardTda2exVision.h
 *
 *  \brief TDA2EX Vision board data.
 */

#ifndef BSP_BOARD_TDA2EX_VISION_H_
#define BSP_BOARD_TDA2EX_VISION_H_

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

#define VPS_CAPT_DRV_ID_TDA2EX_VISION_SII9127           (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_ADV7611           (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_OV1063X           (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_LI_OV1063X        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_APT_AR0132        (FVID2_VPS_CAPT_VID_DRV)

#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_SII9127 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_ADV7611 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_LI_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_APT_AR0132 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2EX_VISION_SII9127           (0U)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_ADV7611           (0U)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_OV1063X           (0U)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_LI_OV1063X        (0U)
#define VPS_CAPT_DRV_ID_TDA2EX_VISION_APT_AR0132        (0U)

#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_SII9127      (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_ADV7611      (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_OV1063X      (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_LI_OV1063X   (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_APT_AR0132   (0U)

#endif

#ifdef TI814X_FAMILY_BUILD

/* I2C is connected to I2C2 in case of TI814x interposer */
#define BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_SII9127  (BSP_DEVICE_I2C_INST_ID_2)
#define BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_ADV7611  (BSP_DEVICE_I2C_INST_ID_2)
#define BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_OV1063X  (BSP_DEVICE_I2C_INST_ID_2)

#else

#define BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_SII9127  (BSP_DEVICE_I2C_INST_ID_4)
#define BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_ADV7611  (BSP_DEVICE_I2C_INST_ID_4)
#define BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_OV1063X  (BSP_DEVICE_I2C_INST_ID_4)

#endif

#define BSP_BOARD_TDA2EX_VISION_DEVDATA                                     \
    {                                                                       \
        {                                                                   \
            FVID2_VID_DEC_SII9127_DRV,                    /* devDrvId */    \
            0U,                                           /* instId */      \
            BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_SII9127, /* i2cInstId */   \
            BOARD_SII9127_I2C_ADDR_1,                     /* i2cAddr */     \
            VPS_CAPT_DRV_ID_TDA2EX_VISION_SII9127,        /* drvId */       \
            VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_SII9127,   /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2exVision,           /* selectDev */   \
            NULL,                                         /* resetDev */    \
            NULL,                                         /* powerOnDev */  \
        },                                                                  \
        {                                                                   \
            FVID2_VID_DEC_ADV7611_DRV,                    /* devDrvId */    \
            BSP_DEVICE_ADV7611_INST_ID_0,                 /* instId */      \
            BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_ADV7611, /* i2cInstId */   \
            BOARD_ADV7611_I2C_ADDR_0,                     /* i2cAddr */     \
            VPS_CAPT_DRV_ID_TDA2EX_VISION_ADV7611,        /* drvId */       \
            VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_ADV7611,   /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2exVision,           /* selectDev */   \
            NULL,                                         /* resetDev */    \
            NULL,                                         /* powerOnDev */  \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_OV1063X_DRV,                 /* devDrvId */    \
            0U,                                           /* instId */      \
            BSP_DEVICE_I2C_INST_ID_TDA2EX_VISION_OV1063X, /* i2cInstId */   \
            BOARD_OV1063x_I2C_ADDR_0,                     /* i2cAddr */     \
            VPS_CAPT_DRV_ID_TDA2EX_VISION_OV1063X,        /* drvId */       \
            VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_OV1063X,   /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2exVision,           /* selectDev */   \
            NULL,                                         /* resetDev */    \
            &Bsp_boardPowerOnDeviceTda2ex,                /* powerOnDev */  \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,               /* devDrvId */   \
            BSP_DEVICE_LI_OV1063X_INST_ID_1,               /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */  \
            BOARD_LI_OV1063X_I2C_ADDR_0,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_VISION_LI_OV1063X,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_LI_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exVision,            /* selectDev */  \
            NULL,                                          /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                 /* powerOnDev */ \
        },                                                                  \
        {                                                                   \
            FVID2_VID_SENSOR_APT_AR0132_DRV,               /* devDrvId */   \
            BSP_DEVICE_APT_AR0132_INST_ID_0,               /* instId */     \
            BSP_DEVICE_I2C_INST_ID_4,                      /* i2cInstId */  \
            BOARD_APT_AR0132_I2C_ADDR_0,                   /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_VISION_APT_AR0132,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2EX_VISION_APT_AR0132, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exVision,            /* selectDev */  \
            NULL,                                          /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2ex,                 /* powerOnDev */ \
        },                                                                  \
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

#endif  /* #ifndef BSP_BOARD_TDA2EX_VISION_H_ */

/* @} */
