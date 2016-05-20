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
 *  \file bspdrv_tlc59108Priv.h
 *
 *  \brief TLC59108 PWM internal header file.
 */

#ifndef BSP_TLC59108_PRIV_H_
#define BSP_TLC59108_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>
#include <common/bsp_config.h>
#include <common/trace.h>
#include <osal/bsp_osal.h>
#include <common/bsp_utils.h>
#include <fvid2/fvid2_dataTypes.h>
#include <platforms/bsp_platform.h>
#include <tlc59108/bsp_tlc59108.h>
#include <devices/bsp_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Driver object state - NOT IN USE. */
#define BSP_TLC59108_OBJ_STATE_UNUSED    (0U)
/** \brief Driver object state - IN USE and IDLE. */
#define BSP_TLC59108_OBJ_STATE_IDLE      (1U)

/* Mask for LEDOUT0 and LEDOUT1 registers */
#define BSP_TLC59108_LEDOUT0_PIN0_MASK        (0x03U)   /* 0000 0011*/
#define BSP_TLC59108_LEDOUT0_PIN0_SHIFT       (0x00U)

#define BSP_TLC59108_LEDOUT0_PIN1_MASK        (0x0CU)   /* 0000 1100*/
#define BSP_TLC59108_LEDOUT0_PIN1_SHIFT       (0x02U)

#define BSP_TLC59108_LEDOUT0_PIN2_MASK        (0x30U)   /* 0011 0000*/
#define BSP_TLC59108_LEDOUT0_PIN2_SHIFT       (0x04U)

#define BSP_TLC59108_LEDOUT0_PIN3_MASK        (0xC0U)   /* 1100 0000*/
#define BSP_TLC59108_LEDOUT0_PIN3_SHIFT       (0x06U)

#define BSP_TLC59108_LEDOUT1_PIN4_MASK        (0x03U)   /* 0000 0011*/
#define BSP_TLC59108_LEDOUT1_PIN4_SHIFT       (0x00U)

#define BSP_TLC59108_LEDOUT1_PIN5_MASK        (0x0CU)   /* 0000 1100*/
#define BSP_TLC59108_LEDOUT1_PIN5_SHIFT       (0x02U)

#define BSP_TLC59108_LEDOUT1_PIN6_MASK        (0x30U)   /* 0011 0000*/
#define BSP_TLC59108_LEDOUT1_PIN6_SHIFT       (0x04U)

#define BSP_TLC59108_LEDOUT1_PIN7_MASK        (0xC0U)   /* 1100 0000*/
#define BSP_TLC59108_LEDOUT1_PIN7_SHIFT       (0x06U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief TLC59108 Global driver object.
 */
typedef struct
{
    BspOsal_SemHandle lock;
    /* Global driver lock. */
} Bsp_Tlc59108Obj;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_TLC59108_PRIV_H_ */
