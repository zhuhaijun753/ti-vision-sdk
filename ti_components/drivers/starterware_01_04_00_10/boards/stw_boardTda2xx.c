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
 *  \file stw_boardTda2xx.c
 *
 *  \brief File containing the Tda2xx STW board functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include <osal/bsp_osal.h>
#include <tda2xx/soc_defines.h>
#include <gpio_v2.h>
#include <platforms/stw_platform.h>
#include "soc.h"
#include "i2clib/lld_hsi2c.h"
#include <devices/stw_device.h>
#include <boards/stw_board.h>
#include <stw_boardPriv.h>
#include <stw_boardTda2xxDefault.h>
#include <stw_boardTda2xxVision.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (20U)

/*  Base board PCF8575 3 (on I2C2) - mappings
 *  P0_0 - SEL_HDMI_I2C2
 *  P0_1 - VIN6_SEL
 *  P0_2 - VIN2_S0
 *  P0_3 - CAM_FPD_MUX_S0
 *  P1_2 - MMC2_BOOT
 */
#define BOARD_PCF8575_VIN2_S0               (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_CAM_FPD_MUX_S0        (PCF8575_P0_3_MASK)
#define BOARD_PCF8575_MMC2_BOOT             (PCF8575_P1_2_MASK)

/*  Base board PCF8575 1 (on I2C1) - mappings
 *  P1_5 - CON_LCD_PWR_DN
 */
#define BOARD_PCF8575_LCDCTRL_POWER_MASK    (PCF8575_P1_5_MASK)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_MUX_SEL             ((uint32_t) SOC_GPIO4_BASE)
#define BOARD_GPIO_PIN_MUX1_SEL0            ((uint32_t) 13U)
#define BOARD_GPIO_PIN_MUX1_SEL1            ((uint32_t) 14U)
#define BOARD_GPIO_PIN_MUX2_SEL0            ((uint32_t) 15U)
#define BOARD_GPIO_PIN_MUX2_SEL1            ((uint32_t) 16U)
#define BOARD_GPIO_BASE_DEMUX_FPD_A         ((uint32_t) SOC_GPIO2_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_B         ((uint32_t) SOC_GPIO1_BASE)
#define BOARD_GPIO_BASE_DEMUX_FPD_C         ((uint32_t) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_DEMUX_FPD_A          ((uint32_t) 29U)
#define BOARD_GPIO_PIN_DEMUX_FPD_B          ((uint32_t) 4U)
#define BOARD_GPIO_PIN_DEMUX_FPD_C          ((uint32_t) 7U)
#define BOARD_GPIO_BASE_POWER_DWN           ((uint32_t) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              ((uint32_t) 17U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief EEPROM ID structure. */
typedef struct boardEepromId
{
    uint32_t header;
    char     boardName[16U];
    uint16_t versionMajor;
    uint16_t versionMinor;
    uint32_t configOption;
    char     reserved[28U];
} boardEepromId_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

static int32_t BOARDSelectDeviceTda2xx(uint32_t devDrvId, uint32_t instId);
static int32_t BOARDPowerOnDeviceTda2xx(uint32_t devDrvId,
                                        uint32_t instId,
                                        uint32_t powerOn);
static int32_t BOARDSelectDeviceTda2xxVision(uint32_t devDrvId, uint32_t instId);
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#ifdef TDA2XX_BUILD
extern boardPinmuxBoardCfg_t
    gBoardTda2xxPinMuxData[NUM_OF_TDA2XXBOARD_PINMUX_CONFIGUARATIONS];
#endif
static boardI2cInstData_t gBoardTda2xxI2cInstData[] =
{
#ifndef STW_DISABLE_I2C0
    {
        HSI2C_INST_0,                       /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    },
#endif
    {
        HSI2C_INST_1,                       /* instId */
        SOC_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    }
};

static boardI2cData_t     gBoardTda2xxI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda2xxI2cInstData) / sizeof (boardI2cInstData_t)),
    /* i2cData */
    gBoardTda2xxI2cInstData,
    /* probeInstId */
    HSI2C_INST_1,
};

static boardDeviceData_t  gBoardTda2xxDevData[BOARD_MAX_DEVICE];

static boardData_t        gBoardTda2xxData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda2xxDevData[0U],
    /* pinMuxData */
#ifdef TDA2XX_BUILD
    &gBoardTda2xxPinMuxData[0U],
#else
    NULL,
#endif
};

static boardDeviceData_t  gBoardTda2xxDefaultDevData[] =
    BOARD_TDA2XX_DEFAULT_DEVDATA;
static boardDeviceData_t  gBoardTda2xxVisionDevData[] =
    BOARD_TDA2XX_VISION_DEVDATA;
static boardData_t        gBoardTda2xxDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda2xxDefaultDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTda2xxDefaultDevData,
    /* pinMuxdata */
    NULL
};
static boardData_t        gBoardTda2xxVisionData =
{
    /* numDev */
    (sizeof (gBoardTda2xxVisionDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTda2xxVisionDevData,
    /* pinMuxdata */
    NULL
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t BOARDTda2xxInit(const boardInitParams_t *pInitPrms)
{
#ifdef TDA2XX_FAMILY_BUILD
    /* Enable GPIO required for video mux as output */
    GPIOModuleEnable(BOARD_GPIO_BASE_MUX_SEL);
    GPIOModuleEnable(BOARD_GPIO_BASE_POWER_DWN);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_A);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_B);
    GPIOModuleEnable(BOARD_GPIO_BASE_DEMUX_FPD_C);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX1_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL0,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_MUX_SEL,
        BOARD_GPIO_PIN_MUX2_SEL1,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_POWER_DWN,
        BOARD_GPIO_PIN_OV_PWDN,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_A,
        BOARD_GPIO_PIN_DEMUX_FPD_A,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_B,
        BOARD_GPIO_PIN_DEMUX_FPD_B,
        GPIO_DIR_OUTPUT);
    GPIODirModeSet(
        BOARD_GPIO_BASE_DEMUX_FPD_C,
        BOARD_GPIO_PIN_DEMUX_FPD_C,
        GPIO_DIR_OUTPUT);
#endif

    return (STW_SOK);
}

boardId_t BOARDGetIdTda2xx(void)
{
    int32_t               retVal  = LLD_HSI2C_FAIL;
    boardId_t             boardId = BOARD_UNKNOWN;
    const boardI2cData_t *i2cData;
    platformId_t          platfrmId;

    i2cData = BOARDGetI2cData();
    if (i2cData != NULL)
    {
        platfrmId = PLATFORMGetId();
        if ((PLATFORM_ID_ZEBU == platfrmId) ||
            (PLATFORM_ID_VIRTIO == platfrmId))
        {
            boardId = BOARD_VISION;
        }
        else
        {
            /*
             * Detect board ID
             */
            /*
             * Probe for SII9127 @ 0x31 address to detect
             * Vision daughter card.
             */
            retVal = DEVICEI2cProbeDevice(
                i2cData->probeInstId,
                BOARD_SII9127_I2C_ADDR_1);
            if (LLD_HSI2C_SUCCESS == retVal)
            {
                boardId = BOARD_VISION;
            }

#ifndef STW_DISABLE_I2C0
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                /*
                 * Probe for EEPROM @ 0x50 address to detect
                 * TDA2XX base board.
                 * Note: This should be the last check as base board is
                 * present by default even when daughter card is present.
                 */
                retVal = DEVICEI2cProbeDevice(
                    HSI2C_INST_0,
                    BOARD_EEPROM_I2C_ADDR_0);
                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    /* Default to vision board when base board is detected.
                     * This is required because in some of the vision
                     * boards, SII9127 HDMI is not populated. And hence even if
                     * vision board is connected, we detect as base board */
                    boardId = BOARD_VISION;
                }
            }
#else
            /* Default to vision board when I2C is disabled as we can't
             * detect base board. */
            if (FVID2_SOK != retVal)
            {
                boardId = BSP_BOARD_VISION;
                retVal  = FVID2_SOK;
            }
#endif
        }
    }
    else
    {
        console_print_string(" \r\nNULL Pointer Detected i2cData : ");
    }
    return (boardId);
}

boardRev_t BOARDGetBaseBoardRevTda2xx(void)
{
    boardRev_t      boardRev = BOARD_REV_A;
#ifndef STW_DISABLE_I2C0
    int32_t         retVal;
    uint8_t         regValue[2];
    uint32_t        i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    boardEepromId_t eepromVal;
    boardId_t       boardId;
    void           *pEepromVal = &eepromVal;

    boardId    = BOARDGetId();
    i2cInst    = HSI2C_INST_0;
    eepromAddr = BOARD_EEPROM_I2C_ADDR_0;
    if (BOARD_BASE_TDA3XX == boardId)
    {
        eepromAddr = BOARD_EEPROM_I2C_ADDR_1;
    }

    /* Send 16-bit page address */
    page        = 0U;
    pageSize    = 48U;
    regValue[0] = page >> 8U;         /* HIGH address */
    regValue[1] = page & 0xFFU;       /* LOW address */
    numRegs     = 2U;
    retVal      = DEVICEI2cRawWrite8(i2cInst, eepromAddr, regValue, numRegs);

    /* Eeprom write cycle time is 5ms - so wait for 5ms after
     * write before reading */
    delay = 5U;
    BspOsal_sleep(delay);

    /* Read 0th page */
    retVal += DEVICEI2cRawRead8(
        i2cInst,
        eepromAddr,
        (UInt8 *) pEepromVal,
        pageSize);
    if ((LLD_HSI2C_SUCCESS == retVal) &&
        (eepromVal.header == 0xAA5533EEU))
    {
        console_print_string("\nEEPROM Base Board Name       : ");
        console_print_string(eepromVal.boardName);

        switch (eepromVal.versionMajor)
        {
            case 0x01U:
                boardRev = BOARD_REV_A;
                break;

            case 0x02U:
                boardRev = BOARD_REV_B;
                break;

            case 0x03U:
                boardRev = BOARD_REV_C;
                break;

            default:
                boardRev = BOARD_REV_B;
                break;
        }
    }
    else
    {
        console_print_string("\nEEPROM read failed!!");
    }
#endif

    return (boardRev);
}

boardRev_t BOARDGetDcRevTda2xx(void)
{
    /* Only one revision of board till date */
    return (BOARD_REV_A);
}

const boardI2cData_t *BOARDGetI2cDataTda2xx(void)
{
    return (&gBoardTda2xxI2cData);
}

const boardData_t *BOARDGetDataTda2xx(void)
{
    uint32_t           numDev;
    boardId_t          boardId;
    boardData_t       *boardDat;
    boardDeviceData_t *tempDevData;

    boardId  = BOARDGetId();
    boardDat = &gBoardTda2xxData;

    /* Copy only for the first time */
    if (0U == boardDat->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda2xxDevData[0U];
        switch (boardId)
        {
            case BOARD_BASE_TDA2XX:
                numDev += gBoardTda2xxDefaultData.numDev;
                /* Array bound check */
                if (numDev < BOARD_MAX_DEVICE)
                {
                    memcpy(
                        tempDevData,
                        gBoardTda2xxDefaultData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda2xxDefaultData.numDev));
                    tempDevData += gBoardTda2xxDefaultData.numDev;
                }
                break;
            case BOARD_VISION:
                numDev += gBoardTda2xxDefaultData.numDev;
                numDev += gBoardTda2xxVisionData.numDev;
                /* Array bound check */
                if (numDev < BOARD_MAX_DEVICE)
                {
                    memcpy(
                        tempDevData,
                        gBoardTda2xxDefaultData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda2xxDefaultData.numDev));
                    tempDevData += gBoardTda2xxDefaultData.numDev;
                    memcpy(
                        tempDevData,
                        gBoardTda2xxVisionData.pDevData,
                        (sizeof (boardDeviceData_t) *
                         gBoardTda2xxVisionData.numDev));
                    tempDevData += gBoardTda2xxVisionData.numDev;
                }
                break;
            case BOARD_UNKNOWN:
            default:
                /* Do nothing as numDev will automatically become 0 in
                 * below code */
                break;
        }

        /* Set the total number of device */
        if (numDev < BOARD_MAX_DEVICE)
        {
            boardDat->numDev = numDev;
        }
        else
        {
            console_print_string("\nInvalid num of devices !!");
        }
    }
    return (boardDat);
}

/* Base EVM mux select */
static int32_t BOARDSelectDeviceTda2xx(uint32_t devDrvId, uint32_t instId)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[2];
    uint32_t i2cInst, ioExpAddr, numRegs;
    uint32_t regValueTemp;

    /*
     * Select base EVM leapord imaging sensor or daughter card input for
     * VIN1 signals.
     *
     * CAM_FPD_MUX_S0 = 0 for base EVM input from leapord imaging sensor.
     * CAM_FPD_MUX_S0 = 1 for daughter card input.
     */
    if (DEVICE_ID_OV1063X == devDrvId)
    {
        i2cInst   = HSI2C_INST_1;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_6;
        numRegs   = 2U;
        retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2C read failed!!");
        }
        /* Configure muxes */
        regValue[0U] |= (uint8_t) (BOARD_PCF8575_CAM_FPD_MUX_S0);

        /* The GPIO4_13 to 16 which is controlling the video mux on vision
         * board is muxed in the base board. This should be selected as well */
        regValue[0U] &= (uint8_t) (~((uint8_t) (BOARD_PCF8575_VIN2_S0)));

        retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2C write failed!!");
        }
    }

    if ((DEVICE_ID_MMC == devDrvId) &&
        (DEVICE_MMC_INST_ID_2 == instId))
    {
        i2cInst   = HSI2C_INST_0;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
        numRegs   = 2U;
        retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2C read failed!!");
        }
        /* Configure muxes */
        regValueTemp =
            ((UInt32) regValue[1U] & ((UInt32) (~BOARD_PCF8575_MMC2_BOOT)));
        regValue[1U] = (UInt8) regValueTemp;

        retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nI2C write failed!!");
        }
    }

    return (retVal);
}

static int32_t BOARDPowerOnDeviceTda2xx(uint32_t devDrvId,
                                        uint32_t instId,
                                        uint32_t powerOn)
{
    int32_t  retVal = STW_SOK;
    uint8_t  regValue[2];
    uint32_t i2cInst, ioExpAddr, numRegs;

    if (DEVICE_ID_LCD == devDrvId)
    {
        if (0U == instId)
        {
            i2cInst   = HSI2C_INST_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_0;
            numRegs   = 2U;
            retVal    = DEVICEI2cRawRead8(i2cInst, ioExpAddr, regValue,
                                          numRegs);
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                console_print_string("\nI2C read failed!!");
            }

            /* Configure muxes to power on LCD */
            regValue[1U] &= (uint8_t) ~(BOARD_PCF8575_LCDCTRL_POWER_MASK);

            retVal += DEVICEI2cRawWrite8(i2cInst, ioExpAddr, regValue,
                                         numRegs);
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                console_print_string("\nI2C write failed!!");
            }
        }
    }

    if (DEVICE_ID_OV1063X == devDrvId)
    {
#ifdef TDA2XX_FAMILY_BUILD
        /*
         * OV_PWDN is controlled by GP6[17]. 0 is ON, 1 is OFF
         */
        if (powerOn == (uint32_t) TRUE)
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_POWER_DWN,
                BOARD_GPIO_PIN_OV_PWDN,
                GPIO_PIN_LOW);
        }
        else
        {
            GPIOPinWrite(
                BOARD_GPIO_BASE_POWER_DWN,
                BOARD_GPIO_PIN_OV_PWDN,
                GPIO_PIN_HIGH);
        }
#endif
    }

    return (retVal);
}

/* Vision card mux select */
static int32_t BOARDSelectDeviceTda2xxVision(uint32_t devDrvId, uint32_t instId)
{
    int32_t retVal = STW_SOK;

    /* Select mux at base EVM level */
    retVal = BOARDSelectDeviceTda2xx(devDrvId, instId);

    if (STW_SOK == retVal)
    {
        if (DEVICE_ID_OV1063X == devDrvId)
        {
            /*
             * Select CPLD mux to select between sensors/decoder in vision
             * daughter card
             *
             * MUX Signal mapping
             * ------------------
             * MUX1_SEL0 - GPIO4_13 (Mux mode 15, muxed with VIN2A_D12)
             * MUX1_SEL1 - GPIO4_14 (Mux mode 15, muxed with VIN2A_D13)
             * MUX2_SEL0 - GPIO4_15 (Mux mode 15, muxed with VIN2A_D14)
             * MUX2_SEL1 - GPIO4_16 (Mux mode 15, muxed with VIN2A_D15)
             *
             *                  MUX1_SEL0     MUX1_SEL1   MUX2_SEL0   MUX2_SEL1
             *                  -----------------------------------------------
             * HDMI Receiver        X             X           0           0
             * LI Imager            0             0           1           0
             * OV Imager            1             0           1           0
             * Aptina Imager        0             1           1           0
             * CAM1/3 FPD Link      X             X           0           1
             *
             */
            /* Above is valid for TDA2xx EVM only */
            if (PLATFORMIsTI814xFamilyBuild())
            {
                /* TODO */
            }
            else
            {
                if (DEVICE_ID_OV1063X == devDrvId)
                {
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL0,
                        GPIO_PIN_HIGH);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX1_SEL1,
                        GPIO_PIN_LOW);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL0,
                        GPIO_PIN_HIGH);
                    GPIOPinWrite(
                        BOARD_GPIO_BASE_MUX_SEL,
                        BOARD_GPIO_PIN_MUX2_SEL1,
                        GPIO_PIN_LOW);
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
    }

    return (retVal);
}

/**
 * \brief   Configures IO pins needed by UART console. This API uses the pin mux
 *          data and configures the pinmux of UART console for default mode
 *
 * \param   uartInstId     Instance number of the UART console
 *
 **/
void BOARDTda2xxConfigConsolePinMux(uint32_t uartInstId)
{
#ifdef TDA2XX_BUILD
    const boardPinmuxBoardCfg_t *pPinmuxData;
    uint32_t i = 0;

    pPinmuxData = &gBoardTda2xxPinMuxData[0U];

    for (i = 0; (DEVICE_ID_INVALID != pPinmuxData[i].moduleId); i++)
    {
        if ((pPinmuxData[i].moduleId == DEVICE_ID_UART) &&
            (pPinmuxData[i].instNum == uartInstId) &&
            (pPinmuxData[i].boardMode == BOARD_MODE_DEFAULT))
        {
            PLATFORMSetPinmuxRegs(pPinmuxData[i].regOffset,
                                  pPinmuxData[i].regVal);
        }
    }
#endif
    return;
}

