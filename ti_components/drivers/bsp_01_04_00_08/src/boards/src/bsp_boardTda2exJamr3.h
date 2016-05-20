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
 *  \file bsp_boardTda2exJamr3.h
 *
 *  \brief TDA2EX JAMR3 board data.
 */

#ifndef BSP_BOARD_TDA2EX_JAMR3_H_
#define BSP_BOARD_TDA2EX_JAMR3_H_

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

#define VPS_CAPT_DRV_ID_TDA2EX_JAMR3_TVP5158        (FVID2_VPS_CAPT_VID_DRV)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_JAMR3_TVP5158 \
    (VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA))

#else

#define VPS_CAPT_DRV_ID_TDA2EX_JAMR3_TVP5158        (0U)
#define VPS_CAPT_DRV_INST_ID_TDA2EX_JAMR3_TVP5158   (0U)

#endif

#define BSP_DEVICE_I2C_INST_ID_JAMR3_TVP5158        (BSP_DEVICE_I2C_INST_ID_4)

#define BSP_BOARD_TDA2EX_JAMR3_DEVDATA                                  \
    {                                                                   \
        {                                                               \
            FVID2_VID_DEC_TVP5158_DRV,                 /* devDrvId */   \
            0U,                                        /* instId */     \
            BSP_DEVICE_I2C_INST_ID_JAMR3_TVP5158,      /* i2cInstId */  \
            BOARD_TVP5158_I2C_ADDR_0,                  /* i2cAddr */    \
            VPS_CAPT_DRV_ID_TDA2EX_JAMR3_TVP5158,      /* drvId */      \
            VPS_CAPT_DRV_INST_ID_TDA2EX_JAMR3_TVP5158, /* drvInstId */  \
            &Bsp_boardSelectDeviceTda2exJamr3,         /* selectDev */  \
            NULL,                                      /* resetDev */   \
            NULL,                                      /* powerOnDev */ \
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

#endif  /* #ifndef BSP_BOARD_TDA2EX_JAMR3_H_ */

/* @} */
