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
 *  \file stw_boardTda2exVision.h
 *
 *  \brief Tda2ex Vision board data.
 */

#ifndef STW_BOARD_TDA2EX_VISION_H_
#define STW_BOARD_TDA2EX_VISION_H_

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

#define BOARD_TDA2EX_VISION_DEVDATA                                     \
    {                                                                   \
        {                                          /* OV Sensor */      \
            DEVICE_ID_OV1063X,                     /* devId */          \
            DEVICE_OV1063X_INST_ID_0,              /* devInstNum */     \
            DEVICE_ID_I2C,                         /* ctrlModId */      \
            DEVICE_I2C_INST_ID_4,                  /* ctrlModInstNum */ \
            BOARD_OV1063x_I2C_ADDR_0,              /* ctrlInfo */       \
            DEVICE_MODULE_ID_VIP,                  /* dataModId */      \
            DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0, /* dataModInstNum */ \
            &BOARDSelectDeviceTda2exVision,        /* pFnSelectDev */   \
            NULL,                                  /* pFnResetDev */    \
            &BOARDPowerOnDeviceTda2ex              /* pFnPowerOnDev */  \
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

#endif  /* #ifndef STW_BOARD_TDA2EX_VISION_H_ */

/* @} */
