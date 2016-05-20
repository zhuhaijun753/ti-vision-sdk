
/* ======================================================================
 *  Copyright (C) 2013 Texas Instruments Incorporated
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  The program may not be used without the written permission
 *  of Texas Instruments Incorporated or against the terms and conditions
 *  stipulated in the agreement under which this program has been
 *  supplied.
 * ==================================================================== */
/**
 *  Component:          SBL
 *
 *  Filename:           sbl_tda2xx_SR0.c
 *
 *  Description:        This file contain AVS Class-0 implementation
 *
 *  Author:              vinoth
 *  Reference:          vayu uboot AVS Class-0 (Nishanth Menon)
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "sbl_tda2xx_pmic.h"
#include "common/stw_types.h"
#include "soc.h"
#include "hw_ctrl_core_pad.h"
#include "hw_ctrl_core_pad_io.h"
#include "hw_ctrl_core.h"
#include "hw_device_prm.h"
#include "hw_ocp_socket_prm.h"
#include "hw_ctrl_wkup.h"
#include "gpio_v2.h"
#include "hsi2c.h"
#include "soc_defines.h"
#include "sbl_tda2xx_platform.h"
#include "sbl_tda2xx_soc_init.h"
#include "hw_types.h"
#include "pm/pm_types.h"
#include "pm/pm_utils.h"
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "pmhal_vm.h"
#include "pmhal_pmic.h"
#include "pmhal_pmicComm.h"
#ifndef TDA2EX_BUILD
#include "pmhal_tps659039.h"
#else
#include "pmhal_tps65917.h"
#endif
#include "pmhal_cm.h"
#include "platform.h"
#include "hsi2c.h"

/* =============================================================================
 * LOCAL Defines
 * =============================================================================
 */
/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define SBL_UTILS_I2C_SYSTEM_CLOCK       (96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define SBL_UTILS_I2C_INTERNAL_CLOCK     (9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define SBL_UTILS_I2C_OUTPUT_CLOCK       (400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define SBL_UTILS_I2C_TIMEOUT_COUNT      (4000U)

/** Write Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_WRITE              (1U)

/** Read Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_READ               (2U)

/* =============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/** \brief Function to set the voltage values of the DSS LDO rails.
 *
 *  \param None
 *
 *  \return None
 */
void DSS_LDO_PWR(void);

/** \brief Function to configure the MMC SD PBIAS voltage from control module.
 *
 *  \param None
 *
 *  \return None
 */
void   MMCSD_LDO_PWR(void);

/**
 * \brief   This function calculates the delay value for CPDE and FDPE.
 *
 * \param   configRegOffset   Offset Address of Config Register.
 *                            Possible Values:CONFIG_REG_3/CONFIG_REG_4
 * \param   divisorValue      Value of the divisor
 *                            Possible Values: 88  for CONFIG_REG_3
 *                                           264 for CONFIG_REG_4
 *
 * \return  delayVal          Calculated Delay Value
 */
static uint32_t calculateDelay(uint32_t configRegOffset, uint32_t divisorValue);

/**
 * \brief   This function calculates the final value to be written to
 *          configuration register using aDelay and gDelay values.
 *
 * \param   aDelay          Value of A delay.
 * \param   gDelay          Value of G Delay.
 * \param   cpde            CPDE Value as previously calculated
 * \param   fpde            FPDE value as previously calculated
 *
 * \return  configRegValue  Calculated Config Register Value
 */
static uint32_t calculateConfigRegister(uint32_t aDelay,
                                        uint32_t gDelay,
                                        uint32_t cpde,
                                        uint32_t fpde);

/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t SblUtilsI2cInit(void);

/**
 * \brief   This function reads a byte from the PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be read.
 * \param   regValue    Pointer to the location where the read value will be
 *                      placed.
 * \param   numRegs     Number of registers to be read.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   uint8_t *regValue,
                                   uint32_t numRegs);

/**
 * \brief   This function writes a byte of data to the register of PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be written.
 * \param   regValue    Pointer to the location where the write value will be
 *                      placed.
 * \param   numRegs     Number of registers to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    const uint8_t *regValue,
                                    uint32_t numRegs);
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWaitForBB(uint32_t i2cNum);

/**
 * \brief  Poll for the given flags and return when any of the flags is set or
 *         timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   flags       Flag to be waited for.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

/**
 * \brief  Write the given number of bytes to the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   data        Data to be written.
 * \param   count       Number of Bytes to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWrite(uint32_t i2cNum,
                                uint8_t slaveAddr, const uint8_t data[],
                                uint8_t count);

/**
 * \brief  Read one byte from the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   value       Data to be read is returned.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cRead(uint32_t i2cNum,
                               uint8_t  slaveAddr,
                               uint8_t *value);

/**
 * \brief Check the status of the transfer and handle the error conditions.
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 * \param   xfr     Transfer Type. Can be any one of SBL_UTILS_I2C_WRITE or
 *                  SBL_UTILS_I2C_READ.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

/* =============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

extern int32_t   gSetVoltRailsStatus;

padDelayConfig_t gPadDelayConfig[] = {
    {0x0,   0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x4,   0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x8,   0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0xC,   0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x10,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x14,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x18,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x20,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x24,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x28,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x30,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x34,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x38,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C,  0x5000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x40,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x44,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x48,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x4C,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x50,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x54,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x58,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x5C,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x60,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x64,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x68,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x6C,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x70,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x74,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x78,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x7C,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x80,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x84,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x88,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x8C,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x90,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x94,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x98,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x9C,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA0,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA4,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA8,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xAC,  0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xB0,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB8,  0x70001, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0xBC,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC8,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xCC,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD0,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD4,  0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8,  0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0xDC,  0x40100, {0x8D0, 0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_CLK0, 0x40100, {CFG_VIN1A_CLK0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xE0,  0xC0006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1B_CLK1, 0xC0006, {N/A}, {N/A}, {N/A}} **/
    {0xE4,  0x40100, {0x9FC, 1847, 683 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_DE0, 0x40100, {CFG_VIN1A_DE0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xE8,  0x40100, {0xA08, 2036, 787 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_FLD0, 0x40100, {CFG_VIN1A_FLD0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xEC,  0x40100, {0xA14, 1939, 789 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_HSYNC0, 0x40100, {CFG_VIN1A_HSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0xF0,  0x40100, {0xA20, 1807, 893 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_VSYNC0, 0x40100, {CFG_VIN1A_VSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0xF4,  0x40100, {0x8DC, 2095, 566 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D0, 0x40100, {CFG_VIN1A_D0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xF8,  0x40100, {0x960, 1964, 672 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D1, 0x40100, {CFG_VIN1A_D1_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xFC,  0x40100, {0x99C, 1933, 896 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D2, 0x40100, {CFG_VIN1A_D2_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x100, 0x40100, {0x9A8, 1963, 786 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D3, 0x40100, {CFG_VIN1A_D3_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x104, 0x40100, {0x9B4, 2086, 435 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D4, 0x40100, {CFG_VIN1A_D4_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x108, 0x40100, {0x9C0, 1998, 739 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D5, 0x40100, {CFG_VIN1A_D5_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x10C, 0x40100, {0x9CC, 1952, 749 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D6, 0x40100, {CFG_VIN1A_D6_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x110, 0x40100, {0x9D8, 2061, 726 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D7, 0x40100, {CFG_VIN1A_D7_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x114, 0x4010F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D8, 0x4010F, {N/A}, {N/A}, {N/A}} **/
    {0x118, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x11C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x120, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x124, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x128, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x12C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x130, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x134, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D16, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x138, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D17, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x13C, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D18, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x140, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D19, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x144, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D20, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x148, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D21, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x14C, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D22, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x150, 0x40006, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D23, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x154, 0x40100, {0xA38, 0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_CLK0, 0x40100, {CFG_VIN2A_CLK0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x158, 0x40100, {0xB64, 1953, 141 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_DE0, 0x40100, {CFG_VIN2A_DE0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x15C, 0x40100, {0xB70, 2200, 258 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_FLD0, 0x40100, {CFG_VIN2A_FLD0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x160, 0x40100, {0xB7C, 2089, 3   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_HSYNC0, 0x40100, {CFG_VIN2A_HSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x164, 0x40100, {0xB88, 1822, 0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_VSYNC0, 0x40100, {CFG_VIN2A_VSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x168, 0x40100, {0xA44, 1965, 8   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D0, 0x40100, {CFG_VIN2A_D0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x16C, 0x40100, {0xAC8, 1993, 329 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D1, 0x40100, {CFG_VIN2A_D1_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x170, 0x40100, {0xB04, 1872, 0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D2, 0x40100, {CFG_VIN2A_D2_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x174, 0x40100, {0xB10, 2198, 191 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D3, 0x40100, {CFG_VIN2A_D3_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x178, 0x40100, {0xB1C, 1886, 0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D4, 0x40100, {CFG_VIN2A_D4_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x17C, 0x40100, {0xB28, 2233, 166 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D5, 0x40100, {CFG_VIN2A_D5_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x180, 0x40100, {0xB34, 1649, 0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D6, 0x40100, {CFG_VIN2A_D6_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x184, 0x40100, {0xB40, 1890, 33  }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D7, 0x40100, {CFG_VIN2A_D7_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x188, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x18C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x190, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x194, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x198, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D12, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x19C, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D13, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x1A0, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D14, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x1A4, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D15, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x1A8, 0x40003, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D16, 0x40003, {N/A}, {N/A}, {N/A}} **/
    {0x1AC, 0x40003, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D17, 0x40003, {N/A}, {N/A}, {N/A}} **/
    {0x1B0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1B4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1B8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1BC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C0, 0x40005, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D22, 0x40005, {N/A}, {N/A}, {N/A}} **/
    {0x1C4, 0x40005, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D23, 0x40005, {N/A}, {N/A}, {N/A}} **/
    {0x1C8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1CC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_DE, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_FLD, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_HSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_VSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1DC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1EC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1FC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x200, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x204, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x208, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x20C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x210, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x214, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x218, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x21C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D16, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x220, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D17, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x224, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x228, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x22C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x230, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x234, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x238, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x23C, 0xA0000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MDIO_MCLK, 0xA0000, {N/A}, {N/A}, {N/A}} **/
    {0x240, 0xE0000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MDIO_D, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x244, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RMII_MHZ_50_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x248, 0xC010F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART3_RXD, 0xC010F, {N/A}, {N/A}, {N/A}} **/
    {0x24C, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART3_TXD, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x250, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXC, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x254, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXCTL, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x258, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD3, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x25C, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD2, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x260, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD1, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x264, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD0, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x268, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXC, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x26C, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXCTL, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x270, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x274, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x278, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x27C, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x280, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_USB1_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x284, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_USB2_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x288, 0x60003, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_14, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x28C, 0x60003, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_15, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x290, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_16, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x294, 0x4000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK0, 0x4000E, {N/A}, {N/A}, {N/A}} **/
    {0x298, 0x40107, {0xCFC, 0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK1, 0x40107, {CFG_XREF_CLK1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x29C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A8, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_FSX, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2AC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B4, 0xC0107, {0x3C0, 3144, 549 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR0, 0xC0107, {CFG_MCASP1_AXR0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2B8, 0xC0107, {0x414, 2883, 19  }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR1, 0xC0107, {CFG_MCASP1_AXR1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2BC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2CC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D4, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR8, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D8, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR9, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2DC, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR10, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E0, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR11, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E4, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR12, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E8, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR13, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2EC, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR14, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F0, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR15, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F4, 0x40107, {0x4A4, 1904, 0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKX, 0x40107, {CFG_MCASP2_ACLKX_IN,
     * VIP3_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x2F8, 0xC0107, {0x51C, 2112, 84  }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_FSX, 0xC0107, {CFG_MCASP2_FSX_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2FC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x300, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x304, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x308, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x30C, 0xC0107, {0x4C8, 2080, 0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR2, 0xC0107, {CFG_MCASP2_AXR2_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x310, 0xC0107, {0x4D4, 2580, 118 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR3, 0xC0107, {CFG_MCASP2_AXR3_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x314, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR4, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x318, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR5, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x31C, 0x1000E, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR6, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x320, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x324, 0x40107, {0x528, 725,  0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_ACLKX, 0x40107, {CFG_MCASP3_ACLKX_IN,
     * VIP3_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x328, 0xC0107, {0x54C, 2309, 131 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_FSX, 0xC0107, {CFG_MCASP3_FSX_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x32C, 0xC0107, {0x534, 2075, 216 }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR0, 0xC0107, {CFG_MCASP3_AXR0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x330, 0xC0107, {0x540, 712,  1078}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR1, 0xC0107, {CFG_MCASP3_AXR1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x334, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x338, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x33C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x340, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x344, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x348, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x34C, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x350, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x354, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_CLK, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x358, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_CMD, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x35C, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x360, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x364, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT2, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x368, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT3, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x36C, 0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_SDCD, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x370, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_SDWP, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x374, 0x60109, {0xD8,  1615, 2499}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_10, 0x60109, {CFG_GPIO6_10_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x378, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_11, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x37C, 0x60109, {0x678, 4232, 1768}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_CLK, 0x60109, {CFG_MMC3_CLK_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x380, 0x60109, {0x684, 4131, 1768}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_CMD, 0x60109, {CFG_MMC3_CMD_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x384, 0x60109, {0x690, 4012, 1793}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT0, 0x60109, {CFG_MMC3_DAT0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x388, 0x60109, {0x69C, 4003, 1681}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT1, 0x60109, {CFG_MMC3_DAT1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x38C, 0x60109, {0x6A8, 4117, 1381}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT2, 0x60109, {CFG_MMC3_DAT2_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x390, 0x60109, {0x6B4, 4177, 1915}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT3, 0x60109, {CFG_MMC3_DAT3_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x394, 0x60109, {0x6C0, 4148, 1574}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT4, 0x60109, {CFG_MMC3_DAT4_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x398, 0x60109, {0x6CC, 4137, 1419}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT5, 0x60109, {CFG_MMC3_DAT5_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x39C, 0x60109, {0x6D8, 4000, 1614}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT6, 0x60109, {CFG_MMC3_DAT6_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x3A0, 0x60109, {0x6E4, 4153, 1287}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT7, 0x60109, {CFG_MMC3_DAT7_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x3A4, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3A8, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3AC, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B0, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B4, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B8, 0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS2, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3BC, 0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS3, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C0, 0x4000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C4, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_D1, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C8, 0xC000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_D0, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3CC, 0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_CS0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D0, 0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_DCAN1_TX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D4, 0xE000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_DCAN1_RX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_RXD, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x3E4, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_TXD, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x3E8, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_CTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3EC, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_RTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3F0, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_RXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F4, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_TXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F8, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_CTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3FC, 0x6000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_RTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x400, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C1_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x404, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C1_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x408, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C2_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x40C, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C2_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x418, 0x1000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP0, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x41C, 0x1000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP1, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x420, 0x1000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP2, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x424, 0x1000F, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP3, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x430, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TMS, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x434, 0xE0000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TDI, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x438, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TDO, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x43C, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TCLK, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x440, 0x40000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TRSTN, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x444, 0x50000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RTCK, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x448, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_EMU0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x44C, 0x60000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_EMU1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x45C, 0x20000, {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RESETN, 0x20000, {N/A}, {N/A}, {N/A}} **/
    {0x460, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_NMIN_DSP, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x464, 0x0,     {0x0,   0,    0   }, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RSTOUTN, 0x0, {N/A}, {N/A}, {N/A}} **/
};

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalPmicCommI2cOperations_t gPmicI2cfunc = {
    &SblUtilsI2cInit,
    &SblUtilsI2cReadByte,
    &SblUtilsI2cWriteByte
};

/* ============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* None */

/* ============================================================================
 * FUNCTIONS
 * =============================================================================
 */

inline void sbl_delay(uint32_t delay)
{
    uint32_t i;
    for (i = 0; i < (1000U * delay); ++i)
    {}
}

void DSS_LDO_PWR(void)
{
    /* Set the LDO3 and LDON to 1.8 V */
    PMHALPmicSetRegulatorVoltage(PMHAL_PRCM_PMIC_REGULATOR_1V8PHY,
                                 (uint32_t) 1800U,
                                 PM_TIMEOUT_INFINITE);
    PMHALPmicSetRegulatorVoltage(PMHAL_PRCM_PMIC_REGULATOR_1V8PLL,
                                 (uint32_t) 1800U,
                                 PM_TIMEOUT_INFINITE);
}

void   MMCSD_LDO_PWR(void)
{
    /*CTRL_CORE_CONTROL_PBIAS*/
    /*TODO: Fix SD LDO*/

    uint32_t reg_val = 0;

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
        CTRL_CORE_CONTROL_PBIAS, reg_val);
    sbl_delay((uint32_t) 10); /* wait 10 us */
    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
        CTRL_CORE_CONTROL_PBIAS, reg_val);

    /*Enable SDCARD_BIAS_VMODE*/
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK;
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
        CTRL_CORE_CONTROL_PBIAS, reg_val);

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
        CTRL_CORE_CONTROL_PBIAS, reg_val);
    sbl_delay((uint32_t) 150); /* wait 10 us */
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
        CTRL_CORE_CONTROL_PBIAS, reg_val);

    sbl_delay((uint32_t) 150); /* wait 10 us */
}

/**
 * \brief   SBLConfigAllVotageRails function is used to configure AVS and ABB
 *          for all the supported OPP by calling the PMHAL functions.
 *
 * \param   none
 *
 *
 * \return  PM_SUCCESS if opp is proper and voltage can be configured
 *          PM_FAIL/PM_TIMEOUT/PM_BADARGS otherwise
 *
 **/
int32_t SBLConfigAllVotageRails(void)
{
    pmErrCode_t     retVal = PM_SUCCESS;
    pmhalVmOppId_t  oppId;
    const pmhalPmicOperations_t *pmicOps;
    uint32_t        siliconRev;
#ifdef TDA2EX_BUILD
    uint32_t        ivaAvsVolt, gpuAvsVolt, dspeveAvsVolt;
    pmhalPrcmVdId_t maxAvsVdId;
#else
    pmhalPrcmVdId_t vdId;
#endif

    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALPmicCommI2CRegister(&gPmicI2cfunc);

    /* Get the build time set OPP value using which set the OPP */
    oppId = (pmhalVmOppId_t) get_current_opp();

    /*
     * Get the pmic ops and register with the pmic interface.
     */
#ifndef TDA2EX_BUILD
    pmicOps = PMHALTps659039GetPMICOps();
#else
    pmicOps = PMHALTps65917GetPMICOps();
#endif
    retVal = PMHALPmicRegister(pmicOps);

    retVal = PMHALVMSetOpp(PMHAL_PRCM_VD_MPU, oppId, PM_TIMEOUT_INFINITE);

    /* Do not perform CORE AVS for ES1.0 Samples */
    siliconRev = PlatformGetSiliconRev();
    if (0U != siliconRev)
    {
        /* VD_CORE can only support OPP_NOM */
        retVal |= PMHALVMSetOpp(PMHAL_PRCM_VD_CORE,
                                PMHAL_VM_OPP_NOM,
                                PM_TIMEOUT_INFINITE);
    }

#ifndef TDA2EX_BUILD
    /*
     * Set the voltage for PMHAL_PRCM_VD_IVAHD, PMHAL_PRCM_VD_DSPEVE
     * and PMHAL_PRCM_VD_GPU.
     */
    for (vdId = PMHAL_PRCM_VD_IVAHD; vdId < PMHAL_PRCM_VD_RTC; vdId++)
    {
        retVal |= PMHALVMSetOpp(vdId,
                                oppId, PM_TIMEOUT_INFINITE);
    }
#else
    /* On TDA2EX EVM the IVAHD, GPU and DSP EVE rails are ganged. We find the
     * maximum AVS voltage on these lines and then set the voltage to that value
     */
    ivaAvsVolt    = PMHALVMGetAVS0EfuseVoltage(PMHAL_PRCM_VD_IVAHD, oppId);
    gpuAvsVolt    = PMHALVMGetAVS0EfuseVoltage(PMHAL_PRCM_VD_GPU, oppId);
    dspeveAvsVolt = PMHALVMGetAVS0EfuseVoltage(PMHAL_PRCM_VD_DSPEVE, oppId);

    if ((ivaAvsVolt >= gpuAvsVolt) && (ivaAvsVolt >= dspeveAvsVolt))
    {
        maxAvsVdId = PMHAL_PRCM_VD_IVAHD;
    }
    else if ((gpuAvsVolt >= dspeveAvsVolt) && (gpuAvsVolt >= ivaAvsVolt))
    {
        maxAvsVdId = PMHAL_PRCM_VD_GPU;
    }
    else
    {
        maxAvsVdId = PMHAL_PRCM_VD_DSPEVE;
    }

    retVal |= PMHALVMSetOpp(maxAvsVdId,
                            oppId, PM_TIMEOUT_INFINITE);

#endif
    DSS_LDO_PWR();
    MMCSD_LDO_PWR();

    return (int32_t) retVal;
}

/**
 * \brief   scale_iodelay function implements IODelay Recalibration.
 *          IODelay calibration is required if changing to AVS0 voltage,
 *          otherwise there will be some IO timing error versus datasheet.
 *
 * \param   None.
 *
 *
 * \return  none.
 *
 **/
void scale_iodelay(void)
{
    volatile uint32_t dummyRead = 0U;

    /* Unlock the MMR_LOCK1 */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_1,
        UNLOCK_MMR_LOCK1);

    /* Unlock the MMR_LOCK5 */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_5,
        UNLOCK_MMR_LOCK5);

    /* Unlock the global lock */
    HW_WR_REG32(
        SOC_DELAYLINE_BASE + CONFIG_REG_8,
        CONFIG_REG_8_UNLOCK_GLOBAL_LOCK);

    /*
     * Update config_reg2 based on actual sysclk1 frequency.
     * Take sysclock1 period in ps and divide by 5 and write to register.
     * This ensures calibration logic assumes the correct clock reference.
     */
    HW_WR_FIELD32(
        SOC_DELAYLINE_BASE + CONFIG_REG_2,
        CONFIG_REG_2_REFCLK_PERIOD,
        REFCLK_PERIOD_L4ICLK_66_5_MHZ);

    /* Trigger the recalibration */
    HW_WR_FIELD32(
        SOC_DELAYLINE_BASE + CONFIG_REG_0,
        CONFIG_REG_0_CALIBRATION_START,
        0x1);

    /*
     * Read CALIBRATION_START until it is read as 0,
     * indicating recalibration is complete.
     */
    while ((uint32_t) 0U != HW_RD_FIELD32(
               SOC_DELAYLINE_BASE + CONFIG_REG_0,
               CONFIG_REG_0_CALIBRATION_START))
    {}

    /*
     * Isolate all the IO.
     */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS,
        0xC200000U);

    HW_WR_FIELD32(
        SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE_OVERRIDE);

    while ((uint32_t) 0x1U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    HW_WR_FIELD32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_0,
        CTRL_CORE_SMA_SW_0_ISOIN,
        0x1);

    dummyRead = HW_RD_FIELD32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_SMA_SW_0,
        CTRL_CORE_SMA_SW_0_ISOIN);

    HW_WR_FIELD32(
        SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE_NOOVERRIDE);

    while ((uint32_t) 0x0U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    /* Update delay mechanism for each IO with recalibrated values */
    HW_WR_FIELD32(
        SOC_DELAYLINE_BASE + CONFIG_REG_0,
        CONFIG_REG_0_ROM_READ,
        0x1);

    /*
     * Read ROM_READ until it is read as 0,
     * indicating reload is complete.
     */
    while ((uint32_t) 0U != HW_RD_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_0,
                                          CONFIG_REG_0_ROM_READ))
    {}

    /* Configure PAD mux for SoC along with Virtual and Manual Mode Delays */
    SBLPlatformConfigPadMux();

    /*
     * Remove all IOs from isolation.
     */
    HW_WR_FIELD32(
        SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE_OVERRIDE);

    while ((uint32_t) 0x1U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    HW_WR_FIELD32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_0,
        CTRL_CORE_SMA_SW_0_ISOIN,
        0x0U);

    dummyRead = HW_RD_FIELD32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_SMA_SW_0,
        CTRL_CORE_SMA_SW_0_ISOIN);

    HW_WR_FIELD32(
        SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE,
        PRM_IO_PMCTRL_ISOCLK_OVERRIDE_NOOVERRIDE);

    while ((uint32_t) 0x0U != HW_RD_FIELD32(SOC_DEVICE_PRM_BASE + PRM_IO_PMCTRL,
                                            PRM_IO_PMCTRL_ISOCLK_STATUS))
    {}

    /* Lock the MMR_LOCK1 */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_1,
        LOCK_MMR_LOCK1);

    /* Lock the MMR_LOCK5 */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_5,
        LOCK_MMR_LOCK5);

    /* Lock the global lock */
    HW_WR_REG32(
        SOC_DELAYLINE_BASE + CONFIG_REG_8,
        CONFIG_REG_8_LOCK_GLOBAL_LOCK);

    /* Dummy read to remove compiler warning */
    dummyRead = dummyRead;
}

void SBLPlatformConfigPadMux(void)
{
    uint32_t index;
    uint32_t cpde, fpde, configRegValue, modeSelect;
    uint32_t padArraySize = sizeof (gPadDelayConfig) / sizeof (padDelayConfig_t);

    cpde = calculateDelay(CONFIG_REG_3, (uint32_t) 88);
    fpde = calculateDelay(CONFIG_REG_4, (uint32_t) 264);

    for (index = 0; index < padArraySize; index++)
    {
        HW_WR_REG32(
            SOC_CORE_PAD_IO_REGISTERS_BASE +
            (uint32_t) gPadDelayConfig[index].offset,
            gPadDelayConfig[index].regVal);

        modeSelect = gPadDelayConfig[index].regVal &
                     CTRL_CORE_PAD_GPMC_AD0_MODE_SELECT_MASK;

        if ((0U != modeSelect) &&
            (0U != gPadDelayConfig[index].delayConfigIn.offset))
        {
            configRegValue = calculateConfigRegister(
                gPadDelayConfig[index].delayConfigIn.aDelay,
                gPadDelayConfig[index].delayConfigIn.gDelay,
                cpde,
                fpde);

            HW_WR_REG32(
                SOC_DELAYLINE_BASE +
                (uint32_t) gPadDelayConfig[index].delayConfigIn.offset,
                configRegValue);
        }
        if ((0U != modeSelect) &&
            (0U != gPadDelayConfig[index].delayConfigOen.offset))
        {
            configRegValue = calculateConfigRegister(
                gPadDelayConfig[index].delayConfigOen.aDelay,
                gPadDelayConfig[index].delayConfigOen.gDelay,
                cpde,
                fpde);

            HW_WR_REG32(
                SOC_DELAYLINE_BASE +
                (uint32_t) gPadDelayConfig[index].delayConfigOen.offset,
                configRegValue);
        }
        if ((0U != modeSelect) &&
            (0U != gPadDelayConfig[index].delayConfigOut.offset))
        {
            configRegValue = calculateConfigRegister(
                gPadDelayConfig[index].delayConfigOut.aDelay,
                gPadDelayConfig[index].delayConfigOut.gDelay,
                cpde,
                fpde);

            HW_WR_REG32(
                SOC_DELAYLINE_BASE +
                (uint32_t) gPadDelayConfig[index].delayConfigOut.offset,
                configRegValue);
        }
    }
}

static uint32_t calculateConfigRegister(uint32_t aDelay,
                                        uint32_t gDelay,
                                        uint32_t cpde,
                                        uint32_t fpde)
{
    uint32_t gDelayCoarse, gDelayFine, aDelayCoarse, aDelayFine;
    uint32_t coarseElements, fineElements, totalDelay;
    uint32_t finalConfigRegValue = 0U;

    gDelayCoarse = gDelay / 920U;
    gDelayFine   = ((gDelay % 920U) * 10U) / 60U;

    aDelayCoarse = aDelay / cpde;
    aDelayFine   = ((aDelay % cpde) * 10U) / fpde;

    coarseElements = gDelayCoarse + aDelayCoarse;
    fineElements   = (gDelayFine + aDelayFine) / 10U;

    if (22U < fineElements)
    {
        totalDelay     = (coarseElements * cpde) + (fineElements * fpde);
        coarseElements = totalDelay / cpde;
        fineElements   = (totalDelay % cpde) / fpde;
    }

    finalConfigRegValue = (0x29400U ^ (coarseElements << 5U)) + fineElements;

    return finalConfigRegValue;
}

static uint32_t calculateDelay(uint32_t configRegOffset, uint32_t divisorValue)
{
    uint32_t refclkPeriod, delayCount, refCount, delayVal;

    refclkPeriod = HW_RD_FIELD32(
        SOC_DELAYLINE_BASE + CONFIG_REG_2,
        CONFIG_REG_2_REFCLK_PERIOD);

    delayCount = HW_RD_FIELD32(
        SOC_DELAYLINE_BASE + configRegOffset,
        CONFIG_REG_3_COARSE_DELAY_COUNT);

    refCount = HW_RD_FIELD32(
        SOC_DELAYLINE_BASE + configRegOffset,
        CONFIG_REG_3_COARSE_REF_COUNT);

    delayVal = (uint32_t)
               (((uint64_t) 10 * (uint64_t) (refCount) *
                 (uint64_t) (refclkPeriod)) /
                ((uint64_t) 2 * (uint64_t) (delayCount) *
                 (uint64_t) (divisorValue)));

    return delayVal;
}

static int32_t SblUtilsI2cInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddr = SOC_I2C1_BASE;

    /* Enable I2C1 for PMIC Communication */
    /*Force Wake-up clock domain l4per*/
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /*
     * Do a soft reset so we can clear any incorrect state and
     * configure to suit the PMIC communication.
     */
    I2CSoftReset(baseAddr);

    /*
     * Ensure that the reset is completed. The RDONE bit is set
     * only when the I2C is enabled, so enable I2C before
     * checking for the reset completion.
     */
    I2CMasterEnable(baseAddr);

    timeout = 50U;  /* Approximately 50ms */
    while ((I2CSystemStatusGet(baseAddr) !=
            I2C_SYSS_RDONE_RSTCOMP)
           && (timeout > 0))
    {
        PMUtilsMinDelayMS((uint32_t) 1U);
        timeout--;
    }

    if (timeout == 0)
    {
        status = STW_EFAIL;
    }

    if (status == STW_SOK)
    {
        /* Disable I2C so we can configure for the PMIC communication. */
        I2CMasterEnable(baseAddr);

        /* Configure the I2C BUS clock frequency (I2C_SCL). */
        I2CMasterInitExpClk(baseAddr,
                            SBL_UTILS_I2C_SYSTEM_CLOCK,
                            SBL_UTILS_I2C_INTERNAL_CLOCK,
                            SBL_UTILS_I2C_OUTPUT_CLOCK);

        /*
         * The PMIC communication is always as a master so we don't have
         * to configure the I2C own address. However, it doesn't hurt.
         */
        I2COwnAddressSet(baseAddr, 0,
                         I2C_OWN_ADDR_0);

        /*
         * Make sure the I2C is not in Forced Idle Mode by setting it to No
         * Idle mode.
         */
        I2CSyscInit(baseAddr,
                    (uint32_t) (I2C_AUTOIDLE_DISABLE |
                                I2C_CUT_OFF_BOTH_CLK |
                                I2C_ENAWAKEUP_DISABLE |
                                I2C_NO_IDLE_MODE));

        /*
         * Configure the I2C:
         *    Select Fast/Standard Mode
         *    Select normal mode (vs. start byte mode)
         *    Select 7-bit slave address mode
         *
         * Note that this API writes the 32-bit value passed to the I2C_CON
         * register; the config bits not mentioned below is set to zero.
         */
        I2CConfig(baseAddr, I2C_CFG_N0RMAL_MODE |
                  I2C_CFG_7BIT_SLAVE_ADDR |
                  I2C_OPMODE_FAST_STAND_MODE);

        /* PMIC Comm uses polling mode; disable all the interrupts. */
        I2CMasterIntDisableEx(baseAddr, I2C_INT_ALL);

        /*
         * Bypass the Tx/Rx FIFO. For PRCM access we always read one byte
         * at a time so FIFO is bypassed.
         */
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_TX_MODE);
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_RX_MODE);
        I2CFIFOClear(baseAddr, I2C_TX_MODE);
        I2CFIFOClear(baseAddr, I2C_RX_MODE);

        /* Enable I2C module. */
        I2CMasterEnable(baseAddr);

        /*
         * This is required to ensure that the I2C communication continues
         * even if A15 (the master core) is debug halted on a breakpoint.
         */
        I2CMasterEnableFreeRun(baseAddr);
    }

    /* Clear status register  */
    I2CMasterIntClearEx(baseAddr, I2C_INT_ALL);

    return status;
}

static int32_t SblUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   uint8_t *regValue,
                                   uint32_t numRegs)
{
    int32_t status = STW_SOK;
    status = SblUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == STW_SOK)
    {
        status = SblUtilsI2cRead(i2cNum, (uint8_t) i2cDevAddr, regValue);
    }
    else
    {
        *regValue = 0U;
    }
    return status;
}

static int32_t SblUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    const uint8_t *regValue,
                                    uint32_t numRegs)
{
    uint8_t  data[2];
    uint8_t  count       = (uint8_t) 2U;
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    data[0] = *regAddr;
    data[1] = *regValue;
    status  = SblUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, data, count);

    if (status == STW_SOK)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = SblUtilsI2cWaitForFlags(i2cNum,
                                         I2C_INT_BUS_FREE |
                                         I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t SblUtilsI2cRead(uint32_t i2cNum,
                               uint8_t  slaveAddr,
                               uint8_t *value)
{
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /* Set the slave address */
    I2CMasterSlaveAddrSet(baseAddress,
                          (uint32_t) slaveAddr);

    /* Configure to read 1 data word from the PMIC register.  */
    I2CSetDataCount(baseAddress, (uint32_t) 1U);

    /*
     * Configure i2c as master-receive and enable.
     * Make sure stop condition is generated after the transaction.
     */
    I2CMasterControl(baseAddress,
                     (uint32_t) (I2C_CFG_MST_RX | I2C_CFG_START | I2C_CFG_STOP));

    /* Read the data if the data is ready. */
    status = SblUtilsI2cCheckXfrStatus(i2cNum,
                                       (uint32_t) SBL_UTILS_I2C_READ);
    if (status == STW_SOK)
    {
        *value = I2CMasterDataGet(baseAddress);
    }
    else
    {
        *value = 0U;
    }

    /* Wait for I2C access ready before returning. */
    if (status == STW_SOK)
    {
        uint32_t flags = I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_FREE;
        status = SblUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t SblUtilsI2cWrite(uint32_t i2cNum,
                                uint8_t slaveAddr, const uint8_t data[],
                                uint8_t count)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint8_t  i;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    status = SblUtilsI2cWaitForBB(i2cNum);

    if (status == STW_SOK)
    {
        /* Set the slave address */
        I2CMasterSlaveAddrSet(baseAddress,
                              (uint32_t) slaveAddr);

        /* Configure to send 'count' data words */
        I2CSetDataCount(baseAddress, (uint32_t) count);

        /*
         * Configure i2c as master-transmitter, enable and set start condition.
         * Stop condition is NOT generated as this could be a part of write
         * followed by read (combined format).
         */
        I2CMasterControl(baseAddress,
                         I2C_CFG_MST_TX | I2C_CFG_START);

        /* Transmit 'count' bytes.  */
        for (i = 0; ((i < count) && (status == STW_SOK)); i++)
        {
            /*
             * Check the status to see if the data can be transferred and
             * send data.
             */
            status = SblUtilsI2cCheckXfrStatus(
                i2cNum,
                (uint32_t)
                SBL_UTILS_I2C_WRITE);
            if (status == PM_SUCCESS)
            {
                I2CMasterDataPut(baseAddress, data[i]);
            }

            /* Clear XRDY flags */
            rawSt = I2CMasterIntRawStatus(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_TRANSMIT_READY);
        }

        /*
         * Once we complete writing the 'count' bytes, wait for the
         * ARDY flag to be set. This flag indicates that the I2C
         * is access ready for next transmission. ARDY can also be
         * set if we received NACK so ensure it is not the case.
         */
        if (status == STW_SOK)
        {
            status = SblUtilsI2cWaitForFlags(i2cNum, I2C_INT_ADRR_READY_ACESS);
            if (status == STW_SOK)
            {
                rawSt = I2CMasterIntRawStatus(baseAddress);
                if ((rawSt & I2C_INT_NO_ACK) != 0)
                {
                    status = STW_EFAIL;
                    /* Clear the NACK flag. */
                    I2CMasterIntClearEx(baseAddress,
                                        rawSt & I2C_INT_NO_ACK);
                }

                /* Clear the ARDY flag. */
                I2CMasterIntClearEx(baseAddress,
                                    rawSt & I2C_INT_ADRR_READY_ACESS);
            }
        }
    }

    return status;
}

static int32_t SblUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint32_t flags = I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                     I2C_INT_ARBITRATION_LOST;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    if (xfr == SBL_UTILS_I2C_WRITE)
    {
        flags |= I2C_INT_TRANSMIT_READY;
    }
    else if (xfr == SBL_UTILS_I2C_READ)
    {
        flags |= I2C_INT_RECV_READY;
    }
    else
    {
        status = STW_EFAIL;
    }

    /*
     * Wait for any of the following conditions to occur and
     * handle them in the loop before transmitting data.
     * NACK, AL, XRDY/RRDY, ARDY
     */
    if (status == STW_SOK)
    {
        status = SblUtilsI2cWaitForFlags(i2cNum, flags);
    }

    if (status == STW_SOK)
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);

        /*
         * When I2C is configured as master-transmitter and didn't
         * receive ACK from slave, NACK condition is generated. The
         * following could cause this situation:
         * 1. No receiver is present on the bus with the transmitted
         *    address; board issue
         * 2. Receiver is not ready to communicate with the master
         *    (probably a board/pmic device issue).
         * 3. Receiver gets data or commands it doesn't understand
         *    (incorrect PMIC)
         * 4. Receiver can't receive any more data bytes.
         *
         * NACK can be handled by a master by either generating a
         * STOP condition or a repeated START condition to start
         * a new transfer. In PMIC COMM we generate a STOP
         * condition to abort the transfer and clear the NACK
         * flag.
         *
         * I2C HW clears STT and STP bits in I2C_CON registers.
         */
        if ((rawSt & I2C_INT_NO_ACK) != 0)
        {
            I2CMasterStop(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_NO_ACK);
            status = STW_EFAIL;
        }
        /*
         * Arbitration loss occurs when multiple masters initiate
         * transfer at the same time. Only one master wins and others
         * loose the arbitration. The arbitration loss flag is set
         * if this local host lost the arbitration. After an
         * arbitration loss, the local host can continue to generate
         * clock till the end of the byte transfer on the bus and
         * must restart the transmission. Recovering from arbitration
         * loss slightly complicates the code and this can be added
         * if there is a need. At present we clear the flag  and
         * return error.
         *
         * When arbitration loss occurs, the I2C HW clears the
         * STT, STP and MST bits. The local host switches to the
         * slave mode.
         */
        else if ((rawSt & I2C_INT_ARBITRATION_LOST) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ARBITRATION_LOST);
            status = STW_EFAIL;
        }
        /*
         * ARDY flag is set to indicate that the local host is access
         * ready. We are in the middle of a data transfer and hence
         * it is bad if we get ARDY flag set. For example, if we
         * get NACKed, the ARDY flag is set in the middle of data
         * transfer.
         */
        else if ((rawSt & I2C_INT_ADRR_READY_ACESS) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ADRR_READY_ACESS);
            status = STW_EFAIL;
        }
        /*
         * XRDY flag is set when the TX FIFO is empty or the TX FIFO
         * threshold is not reached. This means the local host can
         * transmit now.
         *
         * RRDY flag is set when the RX FIFO is empty or the RX FIFO
         * threshold is not reached. This means the local host can
         * receive now.
         */
        else if (((xfr == SBL_UTILS_I2C_WRITE) &&
                  ((rawSt & I2C_INT_TRANSMIT_READY) != 0)) ||
                 ((xfr == SBL_UTILS_I2C_READ) &&
                  ((rawSt & I2C_INT_RECV_READY) != 0)))
        {
            /*
             * Return success so that the caller can send/receive the data
             * Note that the caller needs to clear the XRDY/RRDY flag as
             * needed.
             */
            status = STW_SOK;
        }
        else
        {
            /*
             * We should not get here...
             */
            status = STW_EFAIL;
        }
    }

    return status;
}

static int32_t SblUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t rawSt;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    timeout = SBL_UTILS_I2C_TIMEOUT_COUNT;

    rawSt = I2CMasterIntRawStatus(baseAddress);

    while (((rawSt & flags) == 0) && (timeout > 0U))
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);
        timeout--;
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    return status;
}

static int32_t SblUtilsI2cWaitForBB(uint32_t i2cNum)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Clear all current interrupts first.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    for (timeout = SBL_UTILS_I2C_TIMEOUT_COUNT; timeout > 0U; --timeout)
    {
        if (I2CMasterBusBusy(baseAddress) == 0)
        {
            break;
        }
        I2CMasterIntClearEx(baseAddress, I2C_INT_BUS_BUSY);
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    /*
     * Clear all current interrupts.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    return status;
}

