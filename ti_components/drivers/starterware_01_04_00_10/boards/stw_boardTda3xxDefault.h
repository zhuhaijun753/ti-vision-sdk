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
 *  \file stw_boardTda3xxDefault.h
 *
 *  \brief Tda3xx Default board data.
 */

#ifndef STW_BOARD_TDA3XX_DEFAULT_H_
#define STW_BOARD_TDA3XX_DEFAULT_H_

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

#define BOARD_TDA3XX_DEFAULT_DEVDATA                                          \
    {                                                                         \
        {                                                /* EEPROM */         \
            DEVICE_ID_EEPROM,                            /* devId */          \
            DEVICE_EEPROM_INST_ID_0,                     /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            DEVICE_I2C_INST_ID_0,                        /* ctrlModInstNum */ \
            BOARD_EEPROM_I2C_ADDR_1,                     /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART1 */          \
            DEVICE_ID_UART,                              /* devId */          \
            DEVICE_UART_INST_ID_1,                       /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            DEVICE_UART_INST_ID_1,                       /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART2 */          \
            DEVICE_ID_UART,                              /* devId */          \
            DEVICE_UART_INST_ID_2,                       /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            DEVICE_UART_INST_ID_2,                       /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART3*/           \
            DEVICE_ID_UART,                              /* devId */          \
            DEVICE_UART_INST_ID_3,                       /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            DEVICE_UART_INST_ID_3,                       /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* Temp Sensor */    \
            DEVICE_ID_TMP102,                            /* devId */          \
            DEVICE_TEMP_SENSOR_INST_ID_0,                /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            DEVICE_I2C_INST_ID_0,                        /* ctrlModInstNum */ \
            BOARD_TEMP_SENSOR_I2C_ADDR,                  /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* NOR Flash */      \
            DEVICE_ID_NORFLASH,                          /* devId */          \
            DEVICE_NORFLASH_INST_ID_0,                   /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* LCD */            \
            DEVICE_ID_LCD,                               /* devId */          \
            DEVICE_LCD_INST_ID_0,                        /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            DEVICE_I2C_INST_ID_0,                        /* ctrlModInstNum */ \
            BOARD_TLC59108_I2C_ADDR_0,                   /* ctrlInfo */       \
            DEVICE_MODULE_ID_DCTRL,                      /* dataModId */      \
            DEVICE_MODULE_DSS_DISPC_OVLY_DPI1_INST_ID_0, /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda3xx                    /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* OV Sensor */      \
            DEVICE_ID_OV1063X,                           /* devId */          \
            DEVICE_OV1063X_INST_ID_0,                    /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            DEVICE_I2C_INST_ID_1,                        /* ctrlModInstNum */ \
            BOARD_OV1063x_I2C_ADDR_0,                    /* ctrlInfo */       \
            DEVICE_MODULE_ID_VIP,                        /* dataModId */      \
            DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0,       /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* MMC4 */           \
            DEVICE_ID_MMC,                               /* devId */          \
            DEVICE_MMC_INST_ID_4,                        /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* MMC4 */           \
            DEVICE_ID_EMAC0PHY,                          /* devId */          \
            DEVICE_EMAC0PHY_INST_ID_0,                   /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* MCSPI1 */         \
            DEVICE_ID_MCSPI,                             /* devId */          \
            DEVICE_MCSPI_INST_ID_1,                      /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            &BOARDSelectDeviceTda3xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        }                                                                     \
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

#endif  /* #ifndef STW_BOARD_TDA3XX_DEFAULT_H_ */

/* @} */
