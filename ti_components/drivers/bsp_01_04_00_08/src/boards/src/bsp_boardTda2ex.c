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
 *  \file bsp_boardTda2ex.c
 *
 *  \brief File containing the Tda2ex BSP board functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <tda2xx/soc_defines.h>
#include <gpio_v2.h>
#include <soc.h>
#include <platforms/bsp_platform.h>
#ifdef VPS_VIP_BUILD
#include <vps/vps_capture.h>
#endif
#ifdef VPS_DSS_BUILD
#include <vps/vps_displayCtrl.h>
#endif
#include <devices/bsp_device.h>
#include <boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <bsp_boardTda2exDefault.h>
#include <bsp_boardTda2exVision.h>
#include <bsp_boardTda2exJamr3.h>
#include <bsp_boardTda2exMultiDes.h>
#ifdef TDA2XX_FAMILY_BUILD
#include <hw/hw_types.h>
#include <hw/hw_ctrl_core_pad_io.h>
#include <hw/hw_ctrl_core_pad.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max of all the devices present in the board including any valid
 * combination of base board and daughter cards */
#define BOARD_MAX_DEVICE                    (20U)

/*  Base board PCF8575 1 (on I2C1) - mappings
 *  P1_5 - CON_LCD_PWR_DN
 */
#define BOARD_PCF8575_LCDCTRL_POWER_MASK    (PCF8575_P1_5_MASK)

/*  Base board PCF8575 2 (on I2C1) - mappings
 *  P0_4 - SEL_ENET_MUX_S0
 */
#define BOARD_PCF8575_SEL_ENET_MUX_S0       (PCF8575_P0_4_MASK)

/*  Base board PCF8575 3 (on I2C5) - mappings
 *  P0_2 - VIN2_S0
 *  P0_6 - VIN2_S2
 *  P0_7 - SEL_VIN4_MUX_S0
 */
#define BOARD_PCF8575_VIN2_S0               (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_VIN2_S2               (PCF8575_P0_6_MASK)
#define BOARD_PCF8575_SEL_VIN4_MUX_S0       (PCF8575_P0_7_MASK)

/* Video mux select for vision daughter card */
#define BOARD_GPIO_BASE_POWER_DWN           ((UInt32) SOC_GPIO6_BASE)
#define BOARD_GPIO_PIN_OV_PWDN              ((UInt32) 17U)

/*  JAMR3 board PCF8575 1 (on I2C1/I2C4) - mappings
 *  P0_0 - BOARD_PCF8575_MMC_CD
 *  P0_1 - BOARD_PCF8575_MMC_WP
 *  P0_2 - HI_ISOL_4
 *  P0_3 - EN_DAB3_4
 *  P0_4 - EN_DABL_4
 *  P0_5 - HI_ISOL_3
 *  P0_6 - EN_DAB3_3
 *  P0_7 - EN_DABL_3
 *  P1_0 - SEL_TVP_FPD
 *  P1_2 - HI_ISOL_2
 *  P1_3 - EN_DAB3_2
 *  P1_4 - EN_DABL_2
 *  P1_5 - HI_ISOL_1
 *  P1_6 - EN_DAB3_1
 *  P1_7 - EN_DABL_1
 */
#define BOARD_PCF8575_MMC_CD                (PCF8575_P0_0_MASK)
#define BOARD_PCF8575_MMC_WP                (PCF8575_P0_1_MASK)
#define BOARD_PCF8575_HI_ISOL_4             (PCF8575_P0_2_MASK)
#define BOARD_PCF8575_EN_DAB3_4             (PCF8575_P0_3_MASK)
#define BOARD_PCF8575_EN_DABL_4             (PCF8575_P0_4_MASK)
#define BOARD_PCF8575_HI_ISOL_3             (PCF8575_P0_5_MASK)
#define BOARD_PCF8575_EN_DAB3_3             (PCF8575_P0_6_MASK)
#define BOARD_PCF8575_EN_DABL_3             (PCF8575_P0_7_MASK)
#define BOARD_PCF8575_SEL_TVP_FPD           (PCF8575_P1_0_MASK)
#define BOARD_PCF8575_HI_ISOL_2             (PCF8575_P1_2_MASK)
#define BOARD_PCF8575_EN_DAB3_2             (PCF8575_P1_3_MASK)
#define BOARD_PCF8575_EN_DABL_2             (PCF8575_P1_4_MASK)
#define BOARD_PCF8575_HI_ISOL_1             (PCF8575_P1_5_MASK)
#define BOARD_PCF8575_EN_DAB3_1             (PCF8575_P1_6_MASK)
#define BOARD_PCF8575_EN_DABL_1             (PCF8575_P1_7_MASK)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief EEPROM ID structure. */
typedef struct
{
    UInt32 header;
    Char   boardName[16U];
    UInt16 versionMajor;
    UInt16 versionMinor;
    UInt32 configOption;
    Char   reserved[28U];
} Bsp_BoardEepromId;

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

static Int32 Bsp_boardPowerOnDeviceTda2ex(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn);
static Int32 Bsp_boardSelectDeviceTda2ex(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2exVision(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2exJamr3(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTda2exMultiDes(UInt32 devDrvId,
                                                 UInt32 instId);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardI2cInstData gBoardTda2exI2cInstData[] =
{
#ifndef BSP_DISABLE_I2C0
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        SOC_I2C1_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT1,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif
#ifdef TDA2XX_FAMILY_BUILD
    {
        BSP_DEVICE_I2C_INST_ID_4,           /* instId */
        SOC_I2C5_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT5,           /* intNum */
        400U                                /* busClkKHz */
    }
#endif
};

static Bsp_BoardI2cData     gBoardTda2exI2cData =
{
    /* numI2c */
    (sizeof (gBoardTda2exI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardTda2exI2cInstData,
    /* probeInstId */
    BSP_DEVICE_I2C_INST_ID_4,
};

static Bsp_BoardDeviceData  gBoardTda2exDevData[BOARD_MAX_DEVICE];

static Bsp_BoardData        gBoardTda2exData =
{
    /* numDev */
    0U,
    /* devData */
    &gBoardTda2exDevData[0U],
};

static Bsp_BoardData        gBoardTda2exCustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

static Bsp_BoardDeviceData  gBoardTda2exDefaultDevData[] =
    BSP_BOARD_TDA2EX_DEFAULT_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2exVisionDevData[] =
    BSP_BOARD_TDA2EX_VISION_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2exJamr3DevData[] =
    BSP_BOARD_TDA2EX_JAMR3_DEVDATA;

static Bsp_BoardDeviceData  gBoardTda2exMultiDesDevData[] =
    BSP_BOARD_TDA2EX_MULTIDES_DEVDATA;

static Bsp_BoardData        gBoardTda2exDefaultData =
{
    /* numDev */
    (sizeof (gBoardTda2exDefaultDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exDefaultDevData,
};

static Bsp_BoardData        gBoardTda2exVisionData =
{
    /* numDev */
    (sizeof (gBoardTda2exVisionDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exVisionDevData,
};

static Bsp_BoardData        gBoardTda2exJamr3Data =
{
    /* numDev */
    (sizeof (gBoardTda2exJamr3DevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exJamr3DevData,
};

static Bsp_BoardData        gBoardTda2exMultiDesData =
{
    /* numDev */
    (sizeof (gBoardTda2exMultiDesDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTda2exMultiDesDevData,
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardTda2exInit(void)
{
#ifdef TDA2XX_FAMILY_BUILD
    /* Enable GPIO required for video mux as output */
    GPIOModuleEnable(BOARD_GPIO_BASE_POWER_DWN);
    GPIODirModeSet(
        BOARD_GPIO_BASE_POWER_DWN,
        BOARD_GPIO_PIN_OV_PWDN,
        GPIO_DIR_OUTPUT);
#endif

    return (BSP_SOK);
}

Bsp_BoardId Bsp_boardGetIdTda2ex(void)
{
    Int32                   retVal;
    Bsp_BoardId             boardId = BSP_BOARD_UNKNOWN;
    const Bsp_BoardI2cData *i2cData;
    Bsp_PlatformId          platformId;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    platformId = Bsp_platformGetId();
    if ((BSP_PLATFORM_ID_ZEBU == platformId) ||
        (BSP_PLATFORM_ID_VIRTIO == platformId))
    {
        boardId = BSP_BOARD_VISION;
    }
    else
    {
        /*
         * Probe for IO Expander 1 in MULTI DES @ 0x25 address to detect
         * MULTI DESERIALISER daughter card.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            BOARD_MULTIDES_IO_EXP_I2C_ADDR_0);
        if (FVID2_SOK == retVal)
        {
            boardId = BSP_BOARD_MULTIDES;
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * Probe for SII9127 @ 0x31 address to detect
             * Vision daughter card.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                BOARD_SII9127_I2C_ADDR_1);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_VISION;
            }
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * Probe for TVP5158 @ 0x58 address to detect
             * JAMR3 daughter card.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                BOARD_TVP5158_I2C_ADDR_0);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_JAMR3;
            }
        }

#ifndef BSP_DISABLE_I2C0
        if (FVID2_SOK != retVal)
        {
            /*
             * Probe for EEPROM @ 0x51 address to detect
             * TDA2EX base board.
             * Note: This should be the last check as base board is
             * present by default even when daughter card is present.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                BSP_DEVICE_I2C_INST_ID_0,
                BOARD_EEPROM_I2C_ADDR_1);
            if (FVID2_SOK == retVal)
            {
                /* Default to vision board when base board is detected.
                 * This is required because in some of the vision
                 * boards, SII9127 HDMI is not populated. And hence even if
                 * vision board is connected, we detect as base board */
                boardId = BSP_BOARD_VISION;
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
#endif  /* #ifndef BSP_DISABLE_I2C0 */
    }

    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevTda2ex(void)
{
    Bsp_BoardRev      boardRev = BSP_BOARD_REV_A;
#ifndef BSP_DISABLE_I2C0
    Int32             retVal;
    UInt8             regValue[2];
    UInt32            i2cInst, eepromAddr, page, pageSize, delay, numRegs;
    Bsp_BoardEepromId eepromVal;
    void             *pEepromVal = &eepromVal;

    i2cInst    = BSP_DEVICE_I2C_INST_ID_0;
    eepromAddr = (UInt32) BOARD_EEPROM_I2C_ADDR_1;

    /* Send 16-bit page address */
    page        = 0U;
    pageSize    = 48U;
    regValue[0] = page >> 8U;         /* HIGH address */
    regValue[1] = page & 0xFFU;       /* LOW address */
    numRegs     = 2U;
    retVal      = Bsp_deviceRawWrite8(i2cInst, eepromAddr, regValue, numRegs);

    /* Eeprom write cycle time is 5ms - so wait for 5ms after
     * write before reading */
    delay = 5U;
    BspOsal_sleep(delay);

    /* Read 0th page */
    retVal += Bsp_deviceRawRead8(
        i2cInst,
        eepromAddr,
        (UInt8 *) pEepromVal,
        pageSize);
    if ((FVID2_SOK == retVal) &&
        (eepromVal.header == 0xAA5533EEU))
    {
        GT_1trace(BspBoardTrace, GT_INFO,
                  " EEPROM Base Board Name: [%s]\n", eepromVal.boardName);
        switch (eepromVal.versionMajor)
        {
            case 0x01U:
                boardRev = BSP_BOARD_REV_A;
                break;

            case 0x02U:
                boardRev = BSP_BOARD_REV_B;
                break;

            case 0x03U:
                boardRev = BSP_BOARD_REV_C;
                break;

            case 0x04U:
                boardRev = BSP_BOARD_REV_D;
                break;

            case 0x05U:
                boardRev = BSP_BOARD_REV_E;
                break;

            default:
                boardRev = BSP_BOARD_REV_E;
                break;
        }
    }
    else
    {
        GT_0trace(BspBoardTrace, GT_ERR, "EEPROM read failed!!\n");
    }
#endif

    return (boardRev);
}

Bsp_BoardRev Bsp_boardGetDcRevTda2ex(void)
{
    Int32        retVal;
    Bsp_BoardId  boardId;
    Bsp_BoardRev boardRev = BSP_BOARD_REV_A;
    const Bsp_BoardI2cData *i2cData;

    boardId = Bsp_boardGetId();
    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if ((BSP_BOARD_VISION == boardId) || (BSP_BOARD_MULTIDES == boardId))
    {
        /*
         * REV D boards doesn't have SII9127 and instead have ADV7611.
         * Probe for SII9127 @ 0x31 address to detect < REV D boards.
         */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            BOARD_SII9127_I2C_ADDR_1);
        if (FVID2_SOK != retVal)
        {
            /* No SII9127 detected, so REV D boards */
            boardRev = BSP_BOARD_REV_D;
        }
    }

    return (boardRev);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cDataTda2ex(void)
{
    return (&gBoardTda2exI2cData);
}

const Bsp_BoardData *Bsp_boardGetDataTda2ex(void)
{
    UInt32               numDev;
    Bsp_BoardId          boardId;
    Bsp_BoardData       *boardData;
    Bsp_BoardDeviceData *tempDevData;

    boardId   = Bsp_boardGetId();
    boardData = &gBoardTda2exData;

    /* Copy only for the first time */
    if (0U == boardData->numDev)
    {
        /* Copy the individual board data to global board data as per
         * hierarchy */
        numDev      = 0U;
        tempDevData = &gBoardTda2exDevData[0U];
        switch (boardId)
        {
            case BSP_BOARD_BASE_TDA2EX:
                numDev += gBoardTda2exDefaultData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                break;

            case BSP_BOARD_VISION:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exVisionData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exVisionData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exVisionData.numDev));
                tempDevData += gBoardTda2exVisionData.numDev;
                break;

            case BSP_BOARD_JAMR3:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exJamr3Data.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exJamr3Data.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exJamr3Data.numDev));
                tempDevData += gBoardTda2exJamr3Data.numDev;
                break;

            case BSP_BOARD_MULTIDES:
                numDev += gBoardTda2exDefaultData.numDev;
                numDev += gBoardTda2exVisionData.numDev;
                numDev += gBoardTda2exMultiDesData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exDefaultData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exDefaultData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exVisionData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exVisionData.numDev));
                tempDevData += gBoardTda2exVisionData.numDev;
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exMultiDesData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exMultiDesData.numDev));
                tempDevData += gBoardTda2exMultiDesData.numDev;
                break;

            case BSP_BOARD_CUSTOM:
                numDev += gBoardTda2exCustomData.numDev;
                /* Array bound check */
                GT_assert(BspBoardTrace, numDev < BOARD_MAX_DEVICE);
                BspUtils_memcpy(
                    tempDevData,
                    gBoardTda2exCustomData.devData,
                    (sizeof (Bsp_BoardDeviceData) *
                     gBoardTda2exCustomData.numDev));
                tempDevData += gBoardTda2exDefaultData.numDev;
                break;

            case BSP_BOARD_UNKNOWN:
            default:
                /* Do nothing as numDev will automatically become 0 in
                 * below code */
                break;
        }

        /* Set the total number of device */
        boardData->numDev = numDev;
    }

    return (boardData);
}

/* Base EVM mux select */
static Int32 Bsp_boardSelectDeviceTda2ex(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2], regValue1[2];
    UInt32 i2cInst, i2cInst1, ioExpAddr, ioExpAddr1, numRegs, numRegs1;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTemp, regValueTemp1;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    /*
     * Select base EVM leapord imaging sensor or daughter card input for
     * VIN2 signals.
     *
     * VIN2_S0,VIN2_S2 = 10 for base EVM input from leapord imaging sensor.
     * VIN2_S0,VIN2_S2 = 01 for input from daughter card.
     */
    if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
        (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
        (FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
        (FVID2_VID_DEC_ADV7611_DRV == devDrvId) ||
        (FVID2_VID_DEC_TVP5158_DRV == devDrvId) ||
        (BSP_DRV_ID_ENET_PHY_DP83865 == devDrvId))
    {
        i2cInst   = BSP_DEVICE_I2C_INST_ID_4;
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_6;
        numRegs   = 2U;
        retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\n");
        }

        /* Configure muxes */
        if (BSP_DRV_ID_ENET_PHY_DP83865 == devDrvId)
        {
            i2cInst1   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr1 = BOARD_IO_EXP_I2C_ADDR_1;
            numRegs1   = 2U;
            retVal     = Bsp_deviceRawRead8(
                i2cInst1,
                ioExpAddr1,
                regValue1,
                numRegs1);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\n");
            }

            if (BSP_DEVICE_ENET_PHY_DP83865_INST_ID_1 == instId)
            {
                /* ENET: VIN2_S2=1,VIN2_S0=1 */
                regValueTemp = ((UInt32) regValue[0U] | BOARD_PCF8575_VIN2_S0);
                regValue[0U] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[0U] | BOARD_PCF8575_VIN2_S2);
                regValue[0U] = (UInt8) regValueTemp;

                /* ENET: SEL_ENET_MUX_S0=1 */
                regValueTemp1 =
                    ((UInt32) regValue1[0U] | BOARD_PCF8575_SEL_ENET_MUX_S0);
                regValue1[0U] = (UInt8) regValueTemp1;
            }
            else
            {
                /* When user want to use port 0, we are routing EMAC[1] signal
                 * coming from the ENET phy to EMAC[0] pads using the
                 * SEL_ENET_MUX_S0 signal. In this case the video muxes
                 * are not used and hence not changed */
                /* ENET: SEL_ENET_MUX_S0=0 */
                regValueTemp1 =
                    ((UInt32) regValue1[0U] &
                     ((UInt32) (~BOARD_PCF8575_SEL_ENET_MUX_S0)));
                regValue1[0U] = (UInt8) regValueTemp1;
            }

            retVal += Bsp_deviceRawWrite8(
                i2cInst1,
                ioExpAddr1,
                regValue1,
                numRegs1);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
            }
        }
        else
        {
            if ((FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) &&
                (BSP_DEVICE_LI_OV1063X_INST_ID_0 == instId))
            {
                /* CAM: VIN2_S2=0,VIN2_S0=1 */
                regValueTemp =
                    ((UInt32) regValue[0U] &
                     ((UInt32) (~BOARD_PCF8575_VIN2_S2)));
                regValue[0U] = (UInt8) regValueTemp;
                regValueTemp = ((UInt32) regValue[0U] | BOARD_PCF8575_VIN2_S0);
                regValue[0U] = (UInt8) regValueTemp;
            }
            else
            {
                /* VIN2: VIN2_S2=1,VIN2_S0=0 */
                regValueTemp = ((UInt32) regValue[0U] | BOARD_PCF8575_VIN2_S2);
                regValue[0U] = (UInt8) regValueTemp;
                regValueTemp =
                    ((UInt32) regValue[0U] &
                     ((UInt32) (~BOARD_PCF8575_VIN2_S0)));
                regValue[0U] = (UInt8) regValueTemp;
            }
        }

        if (BSP_DRV_ID_ENET_PHY_DP83865 == devDrvId)
        {
            /* SEL_VIN4_MUX_S0 should be 1 for ENET MDIO signals */
            regValueTemp =
                ((UInt32) regValue[0U] | BOARD_PCF8575_SEL_VIN4_MUX_S0);
            regValue[0U] = (UInt8) regValueTemp;
        }
        else
        {
            if ((FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) &&
                (BSP_DEVICE_MULDES_OV1063X_INST_ID_4 == instId))
            {
                /* SEL_VIN4_MUX_S0 should be 0 for VIN1B */
                regValueTemp =
                    ((UInt32) regValue[0U] &
                     ((UInt32) (~BOARD_PCF8575_SEL_VIN4_MUX_S0)));
                regValue[0U] = (UInt8) regValueTemp;
            }
        }

        retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
        }
    }

    return (retVal);
}

/* Base EVM power on */
static Int32 Bsp_boardPowerOnDeviceTda2ex(UInt32 devDrvId,
                                          UInt32 instId,
                                          UInt32 powerOn)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTemp;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if (FVID2_LCD_CTRL_DRV == devDrvId)
    {
        if (0U == instId)
        {
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_0;
            numRegs   = 2U;
            retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue,
                                           numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\n");
            }

            /* Configure muxes to power on LCD */
            regValueTemp =
                ((UInt32) regValue[1U] &
                 ((UInt32) ~(BOARD_PCF8575_LCDCTRL_POWER_MASK)));
            regValue[1U] = (UInt8) regValueTemp;

            retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue,
                                          numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
            }
        }
    }

    if (FVID2_VID_SENSOR_OV1063X_DRV == devDrvId)
    {
#ifdef TDA2XX_FAMILY_BUILD
        /*
         * OV_PWDN is controlled by GP6[17]. 0 is ON, 1 is OFF
         */
        if (powerOn == (UInt32) TRUE)
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

static Int32 Bsp_boardSelectDeviceTda2exMultiDes(UInt32 devDrvId,
                                                 UInt32 instId)
{
    Int32 retVal = BSP_SOK;

    /* Select mux at Vision App Board level */
    retVal += Bsp_boardSelectDeviceTda2exVision(devDrvId, instId);

    return retVal;
}

/* Vision card mux select */
static Int32 Bsp_boardSelectDeviceTda2exVision(UInt32 devDrvId, UInt32 instId)
{
    Int32 retVal = BSP_SOK;

    /* Select mux at base EVM level */
    retVal = Bsp_boardSelectDeviceTda2ex(devDrvId, instId);

    if (BSP_SOK == retVal)
    {
        if ((FVID2_VID_SENSOR_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_LI_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId) ||
            (FVID2_VID_SENSOR_APT_AR0132_DRV == devDrvId) ||
            (FVID2_VID_DEC_SII9127_DRV == devDrvId) ||
            (FVID2_VID_DEC_ADV7611_DRV == devDrvId))
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

            /*
             * Note: The GPIO's are not routed to the VISION card in case of
             * TDA2Ex EVM. Hence the mux control is done through the SW3 of the
             * Vision card (Set SW3-8 to ON).
             * This comment is given just for reference so that the same could
             * be set in SW3. Note a 1 here means switch is OFF and viceversa.
             */
        }
    }

    return (retVal);
}

/* JAMR3 card mux select */
static Int32 Bsp_boardSelectDeviceTda2exJamr3(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    UInt32 regValueTemp;

    /* Select mux at base EVM level */
    retVal = Bsp_boardSelectDeviceTda2ex(devDrvId, instId);

    if (BSP_SOK == retVal)
    {
        if (FVID2_VID_DEC_TVP5158_DRV == devDrvId)
        {
            i2cInst   = BSP_DEVICE_I2C_INST_ID_0;
            ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
            numRegs   = 2U;
            retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue,
                                           numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\n");
            }

            /* Configure muxes */
            regValueTemp =
                ((UInt32) regValue[1U] & ((UInt32) (~BOARD_PCF8575_SEL_TVP_FPD)));
            regValue[1U] = (UInt8) regValueTemp;
            retVal      +=
                Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
            }
        }
    }

    return (retVal);
}

Int32 Bsp_boardSetPinMuxTda2ex(
    UInt32        drvId,
    UInt32        instId,
    Bsp_BoardMode boardMode)
{
#ifdef TDA2XX_FAMILY_BUILD
    #ifdef VPS_VIP_BUILD
    Bsp_BoardId boardId;

    boardId = Bsp_boardGetId();
    #endif

    if (BSP_DRV_ID_UART == drvId)
    {
        if (BSP_DEVICE_UART_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* UART1 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_RXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_TXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_CTSN,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_UART1_RTSN,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_SPI2_D1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_UART_INST_ID_9 == instId)
        {
            /* boardMode is ignored as of now */
            /* UART10 mux
             * PAD=gpio6_14, PIN=uart10_rxd
             * PAD=gpio6_15, PIN=uart10_txd */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 3,
                (UInt32) CTRL_CORE_PAD_GPIO6_14,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 3,
                (UInt32) CTRL_CORE_PAD_GPIO6_15,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

    if (BSP_DRV_ID_I2C == drvId)
    {
        if (BSP_DEVICE_I2C_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C1_SDA,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C1_SCL,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C2 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C2_SDA,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_I2C2_SCL,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_I2C_INST_ID_4 == instId)
        {
            /* boardMode is ignored as of now */
            /* I2C5 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 10,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 10,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

    if (BSP_DRV_ID_MCSPI == drvId)
    {
        if (BSP_DEVICE_MCSPI_INST_ID_0 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI1 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_SCLK,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_D1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_D0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI1_CS0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_1 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI2 mux */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_SCLK,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_D1,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_D0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_SPI2_CS0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI3 mux
             * PAD=uart3_rxd, PIN=spi3_clk
             * PAD=uart3_txd, PIN=spi3_d(1)
             * PAD=rgmii0_txc, PIN=spi3_d(0)
             * PAD=rgmii0_txctl, PIN=spi3_cs(0) */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_UART3_RXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_UART3_TXD,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 7,
                (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_3 == instId)
        {
            /* boardMode is ignored as of now */
            /* SPI4 mux
             * PAD=gpmc_a[8], PIN=spi4_clk
             * PAD=gpmc_a[9], PIN=spi4_d(1)
             * PAD=gpmc_a[10], PIN=spi4_d(0)
             * PAD=gpmc_a[11], PIN=spi4_cs(0) */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A8,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A9,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A10,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A11,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

    if (BSP_DRV_ID_MCASP == drvId)
    {
        if (BSP_DEVICE_MCASP_INST_ID_2 == instId)
        {
            /* boardMode is ignored as of now */
            /* McASP3 mux */
            /* PAD=xref_clk2,PIN=mcasp3_ahclkx */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 3,
                (UInt32) CTRL_CORE_PAD_XREF_CLK2,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_ACLKX,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_FSX,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_AXR0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_MCASP3_AXR1,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else if (BSP_DEVICE_MCASP_INST_ID_5 == instId)
        {
            /* boardMode is ignored as of now */
            /* McASP6 mux (JAMR3) */
            /* PAD = mcasp1_axr[8], PIN = MCASP6_AXR0 */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR8,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[9], PIN = MCASP6_AXR1 */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR9,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[10], PIN = MCASP6_ACLKX */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR10,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = mcasp1_axr[11], PIN = MCASP6_AFSX */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 1,
                (UInt32) CTRL_CORE_PAD_MCASP1_AXR11,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            /* PAD = XREF_CLK1, PIN = MCASP6_AHCLKX */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 4,
                (UInt32) CTRL_CORE_PAD_XREF_CLK1,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else if (BSP_DEVICE_MCSPI_INST_ID_3 == instId)
        {
            /* boardMode is ignored as of now */
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A8,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A9,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A10,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 8,
                (UInt32) CTRL_CORE_PAD_GPMC_A11,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        }
        else
        {
            /* Dummy else */
        }
    }

#ifdef VPS_DSS_BUILD
    if ((FVID2_VPS_DCTRL_DRV == drvId) && (VPS_DSS_DISPC_OVLY_DPI1 == instId))
    {
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_CLK,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_DE,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_FLD,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0,
                                  (UInt32) CTRL_CORE_PAD_VOUT1_HSYNC,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0,
                                  (UInt32) CTRL_CORE_PAD_VOUT1_VSYNC,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D0,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D1,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D2,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D3,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D4,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D5,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D6,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D7,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D8,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D9,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D10,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D11,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D12,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D13,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D14,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D15,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D16,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D17,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D18,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D19,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D20,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D21,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D22,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
        Bsp_platformSetPinmuxRegs((UInt32) 0, (UInt32) CTRL_CORE_PAD_VOUT1_D23,
                                  BSP_PLATFORM_IOPAD_CFG_DEFAULT);
    }
#endif

#ifdef VPS_VIP_BUILD
    /*
     *   In Multi des board the connections are as shown below
     *   CAM2 ---> VIN1A (VIN5A Pads)
     *   CAM4 ---> VIN1B (VIN4B Pads)
     *   CAM1 ---> VIN2A (VIN2A Pads)
     *   CAM3 ---> VIN2B (VIN2B Pads)
     */
    if (FVID2_VPS_CAPT_VID_DRV == drvId)
    {
        if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA) ==
             instId))
        {
#ifdef TDA2EX_BUILD
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1A_GROUP5A);
#endif

            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_GPIO6_10,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT6,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT7,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT5,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT4,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT3,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT2,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT1,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_DAT0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_CMD,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 9U,
                (UInt32) CTRL_CORE_PAD_MMC3_CLK,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0,
                                            VPS_VIP_PORTB) == instId))
        {
#ifdef TDA2EX_BUILD
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_1B_GROUP4B);
#endif

            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_MDIO_MCLK,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 6U,
                (UInt32) CTRL_CORE_PAD_GPMC_A8,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_RGMII0_TXD1,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_MDIO_D,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_UART3_RXD,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_UART3_TXD,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_RGMII0_TXC,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_RGMII0_TXCTL,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_RGMII0_RXC,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_RGMII0_RXCTL,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 5U,
                (UInt32) CTRL_CORE_PAD_RGMII0_RXD3,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1,
                                            VPS_VIP_PORTA) == instId))
        {
#ifdef TDA2EX_BUILD
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP2A);
#endif

            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_VIN2A_CLK0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            if (BSP_BOARD_MULTIDES == boardId)
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_RGMII0_TXD2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_VIN2A_VSYNC0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 0U,
                (UInt32) CTRL_CORE_PAD_VIN2A_DE0,
                BSP_PLATFORM_IOPAD_CFG_DEFAULT);

            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_BT656 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_8BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D1,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D2,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D3,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D4,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D5,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D6,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D7,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }

            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_10BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D8,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D9,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_12BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D10,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D11,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_14BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D12,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D13,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if ((BSP_BOARD_MODE_VIDEO_BT1120 == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_16BIT == boardMode) ||
                (BSP_BOARD_MODE_VIDEO_24BIT == boardMode))
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D14,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D15,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            if (BSP_BOARD_MODE_VIDEO_24BIT == boardMode)
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D16,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D17,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D18,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D19,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D20,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D21,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D22,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 0U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_D23,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
        }
        else if ((VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1,
                                            VPS_VIP_PORTB) == instId))
        {
#ifdef TDA2EX_BUILD
            /* Set the VIN mux at control module level */
            HW_WR_FIELD32(
                (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                 CTRL_CORE_VIP_MUX_SELECT),
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B,
                CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2B_GROUP2B);
#endif

            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_FLD0,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            if (BSP_BOARD_MULTIDES == boardId)
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 3U,
                    (UInt32) CTRL_CORE_PAD_VIN2A_HSYNC0,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            else
            {
                Bsp_platformSetPinmuxRegs(
                    (UInt32) 4U,
                    (UInt32) CTRL_CORE_PAD_GPIO6_10,
                    BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            }
            Bsp_platformSetPinmuxRegs(
                (UInt32) 4U,
                (UInt32) CTRL_CORE_PAD_GPIO6_11,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);

            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D23,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D22,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D21,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D20,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D19,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D18,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D17,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
            Bsp_platformSetPinmuxRegs(
                (UInt32) 2U,
                (UInt32) CTRL_CORE_PAD_VIN2A_D16,
                BSP_PLATFORM_IOPAD_CFG_INPUTENABLE_BI);
        }
        else
        {
            /* Dummy else */
        }
    }
#endif
#endif  /* #ifdef TDA2XX_FAMILY_BUILD */

    return (FVID2_SOK);
}

