/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

 /**
 * \file       qspi.h
 *
 * \brief      This file contains the function prototypes for the device
 *             abstraction layer for QSPI. It also contains some
 *             related macro definitions and enum definitions.
 *
 *             The QSPI module support single, dual and quad read mode
 *             in interrupt and polling mode using QSPI data registers
 *             and also support memory mapped mode.
 *
 * \details    Programming sequence of QSPI is as follows:
 *             -# Enable the functional clock for required QSPI instance.
 *             -# Perform the pin multiplexing for required QSPI instance.
 *             -# Set the QSPI idle mode using the API #QSPIconfigIdleMode.
 *             -# Set Device Control register - clock polarity, phase, CS polarity and data
*                 delay depending on silicon Revision #QSPIsetDeviceControl
 *             -# sets Memory Map Setup register #QSPISetMemoryMapSetup.
 *             -# selects the memory mapped mode in SPI switch register and
 *                configures mapped address for different chip select in
 *                control module using #QSPISetMAddrSpace
 *             -# Read data from QSPI data registers using the API
 *                #QSPIreadData.
 *             -# Write data into QSPI data registers by using the API
 *                #QSPIwriteData.
 *             -# returns the status of the interrupts #QSPIintStatus
 *
 **/

#ifndef QSPI_H_
#define QSPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "hw_qspi.h"
#include "hw_types.h"

/* ========================================================================== */
/*                             Enum Definitions                               */
/* ========================================================================== */
/** qspi_DeviceType_e are the values for QSPI device type used for
 * configurations
 *
 *  \param    DEVICE_TYPE_QSPI4                Quad Fast read at 48 MHz
 *  \param    DEVICE_TYPE_QSPI1                Normal read at 12 MHz
 *
 */
typedef enum {
    DEVICE_TYPE_QSPI4 = 0x01U,
    DEVICE_TYPE_QSPI1 = 0x02U,
    /* Spansion flash device type enum values are kept same as
     * default device types for compatibility */
    DEVICE_TYPE_SPANSION_QSPI4 = 0x01U,
    DEVICE_TYPE_SPANSION_QSPI1 = 0x02U,
    DEVICE_TYPE_MICRON_QSPI4   = 0x11U,
    DEVICE_TYPE_MICRON_QSPI1   = 0x12U,
    DEVICE_TYPE_WINBOND_QSPI4  = 0x21U,
    DEVICE_TYPE_WINBOND_QSPI1  = 0x22U,
    DEVICE_TYPE_ISSI_QSPI4     = 0x31U,
    DEVICE_TYPE_ISSI_QSPI1     = 0x32U,
    DEVICE_TYPE_CUSTOM         = 0xF0U
} qspi_DeviceType_e;

/** qspi_ClockFreq_e are the values for selecting flash clock frequency
 *
 *  \param    QSPI_SCLK_FREQ_64MHz            Select 64 MHz clock
 *  \param    QSPI_SCLK_FREQ_32MHz            Select 32 MHz clock
 *  \param    QSPI_SCLK_FREQ_16MHz            Select 16 MHz clock
 *  \param    QSPI_SCLK_FREQ_96MHz            Select 96 MHz clock
 *  \param    QSPI_SCLK_FREQ_48MHz            Select 48 MHz clock
 *  \param    QSPI_SCLK_FREQ_24MHz            Select 24 MHz clock
 *  \param    QSPI_SCLK_FREQ_12MHz            Select 12 MHz clock
 *
 */
typedef enum {
    QSPI_SCLK_FREQ_64MHz = 0x01U,
    QSPI_SCLK_FREQ_32MHz = 0x03U,
    QSPI_SCLK_FREQ_16MHz = 0x07U,
    QSPI_SCLK_FREQ_96MHz = 0x11U,
    QSPI_SCLK_FREQ_48MHz = 0x13U,
    QSPI_SCLK_FREQ_24MHz = 0x17U,
    QSPI_SCLK_FREQ_12MHz = 0x1FU
} qspi_ClockFreq_e;
/** Values of qspi_ClockFreq_e are combination of input clock select value and
 *  Clock devide value.
 *
 *  @def    QSPI_CLKSWITCH_MASK            - Mask value to get input clock value
 *  @def    QSPI_CLKDIVIDER_MASK           - Mask value to get clock devide
 *                                           value
 *
 */
#define QSPI_CLKSWITCH_MASK  0xF0U
#define QSPI_CLKDIVIDER_MASK  0x0FU

/** qspi_ChipSelect_e are the values for selecting Chip select value
 *
 *  \param    QSPI_MMR            Configuration port registers
 *  \param    QSPI_CS0            select chip select 0
 *  \param    QSPI_CS1            select chip select 1
 *  \param    QSPI_CS2            select chip select 2
 *  \param    QSPI_CS3            select chip select 3
 *
 */
typedef enum {
    QSPI_MMR = 0,
    QSPI_CS0 = 1,
    QSPI_CS1 = 2,
    QSPI_CS2 = 3,
    QSPI_CS3 = 4
} qspi_ChipSelect_e;

/** qspi_ReadCommand_e are the values of QSPI commands
 *
 *  \param    QSPI_CMD_READ            Normal Read command
 *  \param    QSPI_CMD_RDSR
 *  \param    QSPI_CMD_WREN            Write enable command
 *  \param    QSPI_CMD_WRREG           Write register command
 *  \param    QSPI_CMD_WRITE           Normal write command
 *  \param    QSPI_CMD_FAST_READ       Fast read command
 *  \param    QSPI_CMD_FAST_DREAD      Fast dual read command
 *  \param    QSPI_CMD_FAST_QREAD      Fast quad read command
 *  \param    QSPI_CMD_MFGID           Read manufacturer Id command
 *  \param    QSPI_CMD_BLKERASE        Block Erase command
 *  \param    QSPI_CMD_PAGEERASE       Page Erase command
 *  \param    QSPI_CMD_FULLERASE       Full Flash Erase command
 *
 */
/* QSPI READ CMD */
typedef enum {
    QSPI_CMD_READ_24       = 0x03U,
    QSPI_CMD_READ          = 0x13U,
    QSPI_CMD_RDSR          = 0x05U,
    QSPI_CMD_RDSR2         = 0x07U,
    QSPI_CMD_RDCR          = 0x35U,
    QSPI_CMD_WREN          = 0x06U,
    QSPI_CMD_WRREG         = 0x01U,
    QSPI_CMD_WRITE_24      = 0x02U,
    QSPI_CMD_WRITE         = 0x12U,
    QSPI_CMD_FAST_READ_24  = 0x0BU,
    QSPI_CMD_FAST_READ     = 0x0CU,
    QSPI_CMD_FAST_DREAD_24 = 0x3BU,
    QSPI_CMD_FAST_DREAD    = 0x3CU,
    QSPI_CMD_FAST_QREAD_24 = 0x6BU,
    QSPI_CMD_FAST_QREAD    = 0x6CU,
    QSPI_CMD_MFGID         = 0x90U,
    QSPI_CMD_BLKERASE_24   = 0xD8U,
    QSPI_CMD_BLKERASE      = 0xDCU,
    QSPI_CMD_PAGEERASE     = 0x21U,
    QSPI_CMD_PAGEERASE_24  = 0x20U,
    QSPI_CMD_FULLERASE     = 0x60U,

    /* Micron flash commands */
    QSPI_CMD_MICRON_READ_24     = 0x03U,
    QSPI_CMD_MICRON_RDSR        = 0x05U,
    QSPI_CMD_MICRON_QREAD_24    = 0x6BU,
    QSPI_CMD_MICRON_WRITE_24    = 0x02U,
    QSPI_CMD_MICRON_MFGID       = 0x9EU,
    QSPI_CMD_MICRON_WREN        = 0x06U,
    QSPI_CMD_MICRON_BLKERASE_24 = 0xD8U,
    QSPI_CMD_MICRON_FULLERASE   = 0xC7U,
    QSPI_CMD_MICRON_RDNVCR      = 0xB5U,
    QSPI_CMD_MICRON_WRNVCR      = 0xB1U,

    /* Winbond specific commands */
    QSPI_CMD_WINBOND_RDSR2 = 0x35U,
    QSPI_CMD_WINBOND_WRSR2 = 0x31U
} qspi_ReadCommand_e;

/* ========================================================================== */
/*                             Structure Definitions                          */
/* ========================================================================== */
/**
 *   Register bitfield definition for Command register.
 *
 */
typedef struct
{
    uint32_t frameLength : 12;
    /**< Frame Length. */
    uint32_t res1        : 2;
    uint32_t wirq        : 1;
    /**< Word Completion Interrupt. */
    uint32_t firq        : 1;
    /**< Frame Completion Interrupt. */
    uint32_t trCmd       : 3;
    /**< Transfer command. */
    uint32_t wordLength  : 7;
    /**< Word Length. */
    uint32_t res2        : 2;
    uint32_t cs          : 2;
    /**< chip Select. */
}HAL_QSPI_Command_t;

/**
 *  Union to access Command register value and bit fields
 *
 */
typedef union
{
    uint32_t           reg;
    /**< 32 bit command register. */
    HAL_QSPI_Command_t regFields;
    /**< structure to access register bit fields. */
}HAL_QSPI_Command_reg;

/**
 *   Register bitfield definition for Device Control register.
 *
 */
typedef struct
{
    uint32_t CKP0  : 1;
    /**<  Clock polarity for chip select 0. */
    uint32_t CSP0  : 1;
    /**<  Chip select polarity for chip select 0. */
    uint32_t CKPH0 : 1;
    /**<  Clock phase for chip select 0. */
    uint32_t DD0   : 2;
    /**<  Data Delay For chip select 0. */
    uint32_t res0  : 3;
    /**<  Reserved bits. */
    uint32_t CKP1  : 1;
    /**<  Clock polarity for chip select 1. */
    uint32_t CSP1  : 1;
    /**<  Chip select polarity for chip select 1. */
    uint32_t CKPH1 : 1;
    /**<  Clock phase for chip select 1. */
    uint32_t DD1   : 2;
    /**<  Data Delay For chip select 1. */
    uint32_t res1  : 3;
    /**<  Reserved bits. */
    uint32_t CKP2  : 1;
    /**<  Clock polarity for chip select 2. */
    uint32_t CSP2  : 1;
    /**<  Chip select polarity for chip select 2. */
    uint32_t CKPH2 : 1;
    /**<  Clock phase for chip select 2. */
    uint32_t DD2   : 2;
    /**<  Data Delay For chip select 2. */
    uint32_t res2  : 3;
    /**<  Reserved bits. */
    uint32_t CKP3  : 1;
    /**<  Clock polarity for chip select 3. */
    uint32_t CSP3  : 1;
    /**<  Chip select polarity for chip select 3. */
    uint32_t CKPH3 : 1;
    /**<  Clock phase for chip select 3. */
    uint32_t DD3   : 2;
    /**<  Data Delay For chip select 3. */
    uint32_t res3  : 3;
    /**<  Reserved bits. */
}HAL_QSPI_DeviceControl_t;
/**
 *  Union to access Device Control register value and bit fields
 *
 */
typedef union
{
    uint32_t                 reg;
    /**<  32 bit Device Control register. */
    HAL_QSPI_DeviceControl_t regFields;
    /**<  structure to access register bit fields. */
}HAL_QSPI_DeviceControl_reg;

/**
 *   Register bitfield definition for Memory Map Setup register.
 *
 */
typedef struct
{
    uint32_t readCmd       : 8;
    /**<  Read command. */
    uint32_t numAddBytes   : 2;
    /**<  Number of Address Bytes (0 = 1 Byte; 1 = 2 Bytes; 2 = 3 Bytes; 3 = 4
     *Bytes). */
    uint32_t numDummyBytes : 2;
    /**<  Number of Dummy bytes for Fast Read ( 1 = use 8 Bits; 2 = Use 16 Bits;
     *3 = Use 24 Bits). */
    uint32_t readType      : 2;
    /**<  Read Type Single Dual or Quad Read Mode. */
    uint32_t res1          : 2;
    uint32_t writeCmd      : 8;
    /**<  Write command. */
    uint32_t numDummyBits  : 6;
    /**<  Number of Dummy bits to use if Dummy Bytes is 0. */
    uint32_t res2          : 2;
}HAL_QSPI_MemMapSetup_t;
/**
 *  Union to access Memory Map Setup register value and bit fields
 *
 */
typedef union
{
    uint32_t               reg;
    /**<  32 bit Memory Map Setup register. */
    HAL_QSPI_MemMapSetup_t regFields;
    /**<  structure to access register bit fields. */
}HAL_QSPI_MemMapSetup_reg;

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
 /* \name Values that can be used by the application for configuration via APIs
*  @{
*/
#define QSPI__SPI_STATUS_REG__BUSY__BUSY 1
#define QSPI__SPI_STATUS_REG__BUSY__IDLE 0

#define QSPI__SPI_CLOCK_CNTRL_REG__CLKEN__DCLOCK_OFF 0
#define QSPI__SPI_CLOCK_CNTRL_REG__CLKEN__DCLOCK_ON 1

#define QSPI__SPI_DC_REG__CKP__DATA_ACTIVE 1
#define QSPI__SPI_DC_REG__CKP__DATA_INACTIVE 0

#define QSPI__SPI_DC_REG__CSP__ACTIVE_LOW 0
#define QSPI__SPI_DC_REG__CSP__ACTIVE_HIGH 1

#define QSPI__SPI_DC_REG__CKPH__CKP_1_SHIFT_OUT_FALLING_EDGE 1
#define QSPI__SPI_DC_REG__CKPH__CKP_1_SHIFT_OUT_RISING_EDGE 0
#define QSPI__SPI_DC_REG__CKPH__CKP_0_SHIFT_OUT_FALLING_EDGE 0
#define QSPI__SPI_DC_REG__CKPH__CKP_0_SHIFT_OUT_RISING_EDGE 1

#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_0 0
#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_1 1
#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_2 2
#define QSPI__SPI_DC_REG__DD__CS_TO_DATA_DELAY_3 3

#define QSPI__SPI_CMD_REG__CSNUM__CS_0 0
#define QSPI__SPI_CMD_REG__CSNUM__CS_1 1
#define QSPI__SPI_CMD_REG__CSNUM__CS_2 2
#define QSPI__SPI_CMD_REG__CSNUM__CS_3 3

#define QSPI__SPI_CMD_REG__FIRQ__FRAME_COUNT_IRQ_DISABLE 0
#define QSPI__SPI_CMD_REG__FIRQ__FRAME_COUNT_IRQ_ENABLE 1

#define QSPI__SPI_CMD_REG__WIRQ__WORD_COUNT_IRQ_DISABLE 0
#define QSPI__SPI_CMD_REG__WIRQ__WORD_COUNT_IRQ_ENABLE 1

#define QSPI__SPI_SETUP0_REG__NUM_A_BYTES__THREE_BYTES   2
#define QSPI__SPI_SETUP0_REG__NUM_A_BYTES__TWO_BYTES     1
#define QSPI__SPI_SETUP0_REG__NUM_A_BYTES__ONE_BYTES     0

#define QSPI__SPI_SETUP0_REG__NUM_D_BYTES__USE_8_BITS    1
#define QSPI__SPI_SETUP0_REG__NUM_D_BYTES__USE_16_BITS   2
#define QSPI__SPI_SETUP0_REG__NUM_D_BYTES__USE_24_BITS   3
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief This function configures the idle mode of the QSPI
 *
 * \param     baseAdd   QSPI base address.
 * \param     idleMode  Idle mode to be configured. Possible values are
 *                      0x0: Force-idle. An idle request is acknowledged
 *                           unconditionally
 *                      0x1: No-idle. An idle request is never acknowledged
 *                      0x2: Smart-idle. Acknowledgement to an idle request is
 *                           given based on the internal activity of the module
 * \return    None
 */
void QSPIconfigIdleMode(uint32_t baseAdd, uint32_t idleMode);

/**
 *  \brief This function sets DCLK_DIV feild in SPICC register and enables clock.
 *
 * \param     baseAdd   QSPI base address.
 * \param     in_ClockSettings  Clock Settings based on enum qspi_ClockFreq_e.
 *
 * \return    None
 */
void QSPISetClockControl(uint32_t baseAdd, qspi_ClockFreq_e in_ClockSettings);

/**
 *  \brief This function sets Device Control register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     value Value to be written to Device Control register
 *
 * \return    None
 */
void QSPIsetDeviceControl(uint32_t baseAdd, uint32_t value);

/**
 *  \brief This function returns value of device control register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Deivce Control register value
 */
uint32_t QSPIgetDeviceControl(uint32_t baseAdd);

/**
 *  \brief This function sets Command register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     cmd Value to be written to Command register
 *
 * \return    None
 */
void QSPIsetCommandReg(uint32_t baseAdd, uint32_t cmd);

/**
 *  \brief This function returns value of Command register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Command register value
 */
uint32_t QSPIgetCommandReg(uint32_t baseAdd);

/**
 *  \brief This function returns value of Status register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Status register value
 */
uint32_t QSPIgetStatus(uint32_t baseAdd);

/**
 *  \brief This function returns Word count value of Status register.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    Word count field in Status register
 */
uint32_t QSPIgetStatusWordCount(uint32_t baseAdd);

/**
 *  \brief This function is blocking and waits till busy bit in status register is
 *  reset.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \return    None
 */
void QSPIWaitIdle(uint32_t baseAdd);

/**
 *  \brief This function writes to data register (data, data1, data2, data3.
 *
 * \param     baseAdd   QSPI base address.
 * \param     data      pointer to source address.
 * \param     length    number of words to be written - accepted values from 1
 *                      to 4.
 *
 * \return    None
 */
void QSPIwriteData(uint32_t baseAdd, const uint32_t *data, int32_t length);

/**
 *  \brief This function reads value of data register (data, data1, data2, data3.
 *
 * \param     baseAdd   QSPI base address.
 * \param     data      pointer to destination address.
 * \param     length    number of words to be read - accepted values from 1
 *                      to 4.
 *
 * \return    None
 */
void QSPIreadData(uint32_t baseAdd, uint32_t *data, int32_t length);

/**
 *  \brief This function sets Memory Map Setup register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     value     Value to be written to Memory Map Setup register
 * \param     chipSelect    External Chip Select value - supported values 0 to 3
 *                          for cs0 to cs3 respectively
 *
 * \return    None
 */
void QSPISetMemoryMapSetup(uint32_t baseAdd, uint32_t value,
                           uint32_t chipSelect);

/**
 *  \brief This function returns value of Memory Map Setup register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     chipSelect    External Chip Select value - supported values 0 to 3
 *                          for cs0 to cs3 respectively
 *
 * \return    Memory Map Setup register value
 */
uint32_t QSPIgetMemoryMapSetup(uint32_t baseAdd, uint32_t chipSelect);

/**
 * \brief This function selects the memory mapped mode in SPI switch register.
 *
 * \param     baseAdd   QSPI base address.
 * \param     MMPT_S    Memory map switch value
 *
 * \return    None
 */
void QSPISetMAddrSpace(uint32_t baseAdd, uint8_t MMPT_S);

/**
 * \brief This Function enables only specified QSPI interrupts
 *
 * \param     baseAdd   QSPI base address.
 * \param   intFlag    mask value for the interrupts to be enabled.
 *
 * \returns None.
 *
 */
void QSPIintEnable(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief This Function disables only specified QSPI interrupts
 *
 * \param     baseAdd   QSPI base address.
 * \param   intFlag    mask value for the interrupts to be enabled.
 *
 * \returns None.
 *
 */
void QSPIintDisable(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief This function gets the status of enabled interrupts
 *
 * \param     baseAdd   QSPI base address.
 *
 * \returns all the enabled interrupts.
 *
 */
uint32_t QSPIgetEnabledIntStatus(uint32_t baseAdd);

/**
 * \brief This function returns the status of interrupts.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \returns all the interrupt status.
 *
 */
uint32_t QSPIintStatus(uint32_t baseAdd);

/**
 * \brief This Function clears the interrupts.
 *
 * \param     baseAdd   QSPI base address.
 * \param   intFlag    mask value for the interrupts to be cleared.
 *
 * \returns None.
 *
 */
void QSPIintClear(uint32_t baseAdd, uint32_t intFlag);

/**
 * \brief This function returns the raw status of interrupts.
 *
 * \param     baseAdd   QSPI base address.
 *
 * \returns all the raw interrupt status.
 *
 */
uint32_t QSPIintRawStatus(uint32_t baseAdd);

/**
 * \brief This Function clears the raw status of interrupts.
 *
 * \param     baseAdd   QSPI base address.
 * \param   intFlag    mask value for the raw status interrupts to be cleared.
 *
 * \returns None.
 *
 */
void QSPIintRawStatusClear(uint32_t baseAdd, uint32_t intFlag);

#ifdef __cplusplus
}
#endif

#endif
/********************************* End of file ******************************/

