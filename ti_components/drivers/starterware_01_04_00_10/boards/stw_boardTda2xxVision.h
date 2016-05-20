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
 *  \file stw_boardTda2xxVision.h
 *
 *  \brief Tda2xx Vision board data.
 */

#ifndef STW_BOARD_TDA2XX_VISION_H_
#define STW_BOARD_TDA2XX_VISION_H_

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

#define BOARD_TDA2XX_VISION_DEVDATA                                     \
    {                                                                   \
        {                                          /* EEPROM */         \
            DEVICE_ID_EEPROM,                      /* devId */          \
            0U,                                    /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            0U,                                    /* ctrlModInstNum */ \
            BOARD_EEPROM_I2C_ADDR_0,               /* ctrlInfo */       \
            INVALID_ID,                            /* dataModId */      \
            INVALID_INST_NUM,                      /* dataModInstNum */ \
            NULL,                                  /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            NULL                                   /* pFnPowerOnDev */  \
        },                                                              \
        {                                          /* UART */           \
            DEVICE_ID_UART,                        /* devId */          \
            0U,                                    /* devInstNum */     \
            INVALID_ID,                            /* ctrlModId */      \
            INVALID_INST_NUM,                      /* ctrlModInstNum */ \
            INVALID_INFO,                          /* ctrlInfo */       \
            DEVICE_ID_UART,                        /* dataModId */      \
            0U,                                    /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xxVision,        /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            NULL                                   /* pFnPowerOnDev */  \
        },                                                              \
        {                                          /* Temp Sensor */    \
            DEVICE_ID_TMP102,                      /* devId */          \
            0U,                                    /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            0U,                                    /* ctrlModInstNum */ \
            BOARD_TEMP_SENSOR_I2C_ADDR,            /* ctrlInfo */       \
            INVALID_ID,                            /* dataModId */      \
            INVALID_INST_NUM,                      /* dataModInstNum */ \
            NULL,                                  /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            NULL                                   /* pFnPowerOnDev */  \
        },                                                              \
        {                                          /* OV Sensor */      \
            DEVICE_ID_OV1063X,                     /* devId */          \
            DEVICE_OV1063X_INST_ID_0,              /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            DEVICE_I2C_INST_ID_1,                  /* ctrlModInstNum */ \
            BOARD_OV1063x_I2C_ADDR_0,              /* ctrlInfo */       \
            DEVICE_MODULE_ID_VIP,                  /* dataModId */      \
            DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0, /* dataModInstNum */ \
            &BOARDSelectDeviceTda2xxVision,        /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda2xx              /* pFnPowerOnDev */  \
        },                                                              \
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

#endif  /* #ifndef STW_BOARD_TDA2XX_VISION_H_ */

/* @} */
