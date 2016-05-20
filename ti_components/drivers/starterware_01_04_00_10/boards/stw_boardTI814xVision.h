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
 *  \file stw_boardTI814xVision.h
 *
 *  \brief TI814x Vision board data.
 */

#ifndef STW_BOARD_TI814X_VISION_H_
#define STW_BOARD_TI814X_VISION_H_

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

#define BOARD_TI814X_VISION_DEVDATA                       \
    {                                                     \
        {                            /* TBD */            \
            INVALID_ID,              /* devId */          \
            0U,                      /* devInstNum */     \
            INVALID_ID,              /* ctrlModId */      \
            INVALID_INST_NUM,        /* ctrlModInstNum */ \
            INVALID_INFO,            /* ctrlInfo */       \
            INVALID_ID,              /* dataModId */      \
            INVALID_INST_NUM,        /* dataModInstNum */ \
            NULL,                    /* pFnSelectDev */   \
            NULL,                    /* pFnResetDev */    \
            NULL                     /* pFnPowerOnDev */  \
        },                                                \
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

#endif  /* #ifndef  STW_BOARD_TI814X_VISION_H_*/

/* @} */
