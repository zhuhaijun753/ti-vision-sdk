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
 *  \file bsp_tlc59108.h
 *
 *  \brief TLC59108 PWM interface file.
 */

#ifndef BSPDRV_TLC59108_H_
#define BSPDRV_TLC59108_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MAX_TLC59108_DEVICES   (0x02U)

#define BSP_TLC59108_PIN0        (0x00U)
#define BSP_TLC59108_PIN1        (0x01U)
#define BSP_TLC59108_PIN2        (0x02U)
#define BSP_TLC59108_PIN3        (0x03U)
#define BSP_TLC59108_PIN4        (0x04U)
#define BSP_TLC59108_PIN5        (0x05U)
#define BSP_TLC59108_PIN6        (0x06U)
#define BSP_TLC59108_PIN7        (0x07U)

/* TLC 59108 Registers */
#define BSP_TLC59108_REG_MODE1         (0x00U)
#define BSP_TLC59108_REG_MODE2         (0x01U)
#define BSP_TLC59108_REG_PWM0          (0x02U)
#define BSP_TLC59108_REG_PWM1          (0x03U)
#define BSP_TLC59108_REG_PWM2          (0x04U)
#define BSP_TLC59108_REG_PWM3          (0x05U)
#define BSP_TLC59108_REG_PWM4          (0x06U)
#define BSP_TLC59108_REG_PWM5          (0x07U)
#define BSP_TLC59108_REG_PWM6          (0x08U)
#define BSP_TLC59108_REG_PWM7          (0x09U)
#define BSP_TLC59108_REG_GRPPWM        (0x0AU)
#define BSP_TLC59108_REG_GRPFRQ        (0x0BU)
#define BSP_TLC59108_REG_LEDOUT0       (0x0CU)
#define BSP_TLC59108_REG_LEDOUT1       (0x0DU)
#define BSP_TLC59108_REG_SUBADR1       (0x0EU)
#define BSP_TLC59108_REG_SUBADR2       (0x0FU)
#define BSP_TLC59108_REG_SUBADR3       (0x10U)
#define BSP_TLC59108_REG_ALLCALLADR    (0x11U)
#define BSP_TLC59108_REG_IREF          (0x12U)
#define BSP_TLC59108_REG_EFLAG         (0x13U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32 deviceI2cInstId;
    /**< I2C device instance ID to use. */
    UInt32 deviceI2cAddr;
    /**< I2C device address for tlc device. */
} Bsp_Tlc59108CreateParams;

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Int32 Bsp_tlc59108Init(void);

Int32 Bsp_tlc59108DeInit(void);

Int32 Bsp_tlc59108WriteReg(UInt32       i2cInstId,
                           UInt32       tlcDevAdd,
                           const UInt8 *regAddr,
                           const UInt8 *regValue,
                           UInt32       numRegs);

Int32 Bsp_tlc59108ReadReg(UInt32       i2cInstId,
                          UInt32       tlcDevAdd,
                          const UInt8 *regAddr,
                          UInt8       *regValue,
                          UInt32       numRegs);

Int32 Bsp_tlc59108SetPin(UInt32 i2cInstId,
                         UInt32 tlcDevAdd,
                         UInt32 pinNum,
                         UInt32 dutyCycle);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSPDRV_TLC59108_H_ */

