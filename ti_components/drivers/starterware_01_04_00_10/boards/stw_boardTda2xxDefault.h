/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file stw_boardTda2xxDefault.h
 *
 *  \brief Tda2xx Default board data.
 */

#ifndef STW_BOARD_TDA2XX_DEFAULT_H_
#define STW_BOARD_TDA2XX_DEFAULT_H_

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

#define BOARD_TDA2XX_DEFAULT_DEVDATA                                          \
    {                                                                         \
        {                                                /* EEPROM */         \
            DEVICE_ID_EEPROM,                            /* devId */          \
            0U,                                          /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            0U,                                          /* ctrlModInstNum */ \
            BOARD_EEPROM_I2C_ADDR_0,                     /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART 1 */         \
            DEVICE_ID_UART,                              /* devId */          \
            1U,                                          /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            1U,                                          /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART 2 */         \
            DEVICE_ID_UART,                              /* devId */          \
            2U,                                          /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            2U,                                          /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* UART 3 */         \
            DEVICE_ID_UART,                              /* devId */          \
            3U,                                          /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            DEVICE_ID_UART,                              /* dataModId */      \
            3U,                                          /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* Temp Sensor */    \
            DEVICE_ID_TMP102,                            /* devId */          \
            0U,                                          /* devInstNum */     \
            DEVICE_ID_I2C,                               /* ctrlModId */      \
            0U,                                          /* ctrlModInstNum */ \
            BOARD_TEMP_SENSOR_I2C_ADDR,                  /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            NULL,                                        /* pFnSelectDev */   \
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
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda2xx                    /* pFnPowerOnDev */  \
        },                                                                    \
        {                                                /* MMC */            \
            DEVICE_ID_MMC,                               /* devId */          \
            DEVICE_MMC_INST_ID_2,                        /* devInstNum */     \
            INVALID_ID,                                  /* ctrlModId */      \
            INVALID_INST_NUM,                            /* ctrlModInstNum */ \
            INVALID_INFO,                                /* ctrlInfo */       \
            INVALID_ID,                                  /* dataModId */      \
            INVALID_INST_NUM,                            /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xx,                    /* pFnSelectDev */   \
            NULL,                                        /* pFnResetDev */    \
            NULL                                         /* pFnPowerOnDev */  \
        },                                                                    \
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

#endif  /* #ifndef STW_BOARD_TDA2XX_DEFAULT_H_ */

/* @} */
