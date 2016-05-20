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
 *  \file bsp_boardTda2xxDefault.h
 *
 *  \brief Tda2xx Default board data.
 */

#ifndef BSP_BOARD_TDA2XX_DEFAULT_H_
#define BSP_BOARD_TDA2XX_DEFAULT_H_

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

#define VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_LI_OV1063X       (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_DEFAULT_LI_OV1063X \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_LI_OV1063X       (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2XX_DEFAULT_LI_OV1063X  (0U)

#endif

#ifdef VPS_DSS_BUILD

#define VPS_DSS_DRV_ID_TDA2XX_DEFAULT_LCD           (FVID2_VPS_DCTRL_DRV)
#define VPS_DSS_DRV_INST_ID_TDA2XX_DEFAULT_LCD      (VPS_DSS_DISPC_OVLY_DPI1)

#else

#define VPS_DSS_DRV_ID_TDA2XX_DEFAULT_LCD           (0U)
#define VPS_DSS_DRV_INST_ID_TDA2XX_DEFAULT_LCD      (0U)

#endif

#define BSP_BOARD_TDA2XX_DEFAULT_DEVDATA                                     \
    {                                                                        \
        {                                                                    \
            FVID2_LCD_CTRL_DRV,                     /* devDrvId */           \
            0U,                                     /* instId */             \
            BSP_DEVICE_I2C_INST_ID_0,               /* i2cInstId */          \
            BOARD_TLC59108_I2C_ADDR_0,              /* i2cAddr */            \
            VPS_DSS_DRV_ID_TDA2XX_DEFAULT_LCD,      /* drvId */              \
            VPS_DSS_DRV_INST_ID_TDA2XX_DEFAULT_LCD, /* drvInstId */          \
            NULL,                                   /* selectDev */          \
            NULL,                                   /* resetDev */           \
            &Bsp_boardPowerOnDeviceTda2xx,          /* powerOnDev */         \
        },                                                                   \
        {                                                                    \
            FVID2_VID_SENSOR_LI_OV1063X_DRV,                /* devDrvId */   \
            BSP_DEVICE_LI_OV1063X_INST_ID_0,                /* instId */     \
            BSP_DEVICE_I2C_INST_ID_1,                       /* i2cInstId */  \
            BOARD_LI_OV1063X_I2C_ADDR_0,                    /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2XX_DEFAULT_LI_OV1063X,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2XX_DEFAULT_LI_OV1063X, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2xx,                   /* selectDev */  \
            NULL,                                           /* resetDev */   \
            &Bsp_boardPowerOnDeviceTda2xx,                  /* powerOnDev */ \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_UART,                               /* devDrvId */    \
            BSP_DEVICE_UART_INST_ID_0,                     /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_UART,                               /* devDrvId */    \
            BSP_DEVICE_UART_INST_ID_1,                     /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_UART,                               /* devDrvId */    \
            BSP_DEVICE_UART_INST_ID_2,                     /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_MCSPI,                              /* devDrvId */    \
            BSP_DEVICE_MCSPI_INST_ID_1,                    /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
        },                                                                   \
        {                                                                    \
            BSP_DRV_ID_MMC,                                /* devDrvId */    \
            BSP_DEVICE_MMC_INST_ID_2,                      /* instId */      \
            NULL,                                          /* i2cInstId */   \
            NULL,                                          /* i2cAddr */     \
            NULL,                                          /* drvId */       \
            NULL,                                          /* drvInstId */   \
            &Bsp_boardSelectDeviceTda2xx,                  /* selectDev */   \
            NULL,                                          /* resetDev */    \
            NULL,                                          /* powerOnDev */  \
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

#endif  /* #ifndef BSP_BOARD_TDA2XX_DEFAULT_H_ */

/* @} */
