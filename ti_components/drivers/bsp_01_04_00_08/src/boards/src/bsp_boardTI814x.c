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
 *  \file bsp_boardTI814x.c
 *
 *  \brief File containing the BSP board functions related to TI814x.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <stdint.h>
#include <hw_types.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <ti814x/soc_defines.h>
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
#include <bsp_boardTI814xVs.h>
#include <bsp_boardTI814xVc.h>
#include <bsp_boardTI814xVision.h>
#include <bsp_boardTI814xCatalog.h>
/* Below is for the interposer board */
#include <bsp_boardTda2xxVision.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Uncomment below macro to enable I2C0 initialization. */
#define BSP_BOARD_ENABLE_I2C0

/* GPIO related changes as required by
 * the NOR modified Vision App boards */
#define CTRL_MODULE_BASE_ADDR   (0x48140000U)
#define PRCM_BASE_ADDR          (0x48180000U)

#define PINCNTL115                   (CTRL_MODULE_BASE_ADDR + 0x09C8U)

#define CM_ALWON_GPIO_1_CLKCTRL_REG  (PRCM_BASE_ADDR + 0x1560U)

#define ENABLE_GPIO             (UInt32) (21U)

#define GPIO_1_OUTPUT_ENABLE    (0x4804C134U)
#define GPIO_1_DATA_OUTPUT      (0x4804C13CU)
#define GPIO_1_SET_DATA_OUTPUT  (0x4804C194U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

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

static void Bsp_boardEnableVisionBoardTI814x(void);
static Int32 Bsp_boardSelectDeviceTI814xCatlog(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTI814xVc(UInt32 devDrvId, UInt32 instId);
static Int32 Bsp_boardSelectDeviceTI814xVisionTI81xx(UInt32 devDrvId,
                                                     UInt32 instId);

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardI2cInstData gBoardTI814xI2cInstData[] =
{
#ifdef BSP_BOARD_ENABLE_I2C0
    {
        BSP_DEVICE_I2C_INST_ID_0,           /* instId */
        CSL_I2C0_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT0,           /* intNum */
        400U                                /* busClkKHz */
    },
#endif
    {
        BSP_DEVICE_I2C_INST_ID_2,           /* instId */
        CSL_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        400U                                /* busClkKHz */
    }
};

static Bsp_BoardI2cData     gBoardTI814xI2cData =
{
    /* numI2c */
    (sizeof (gBoardTI814xI2cInstData) / sizeof (Bsp_BoardI2cInstData)),
    /* i2cData */
    gBoardTI814xI2cInstData,
    /* probeInstId */
    BSP_DEVICE_I2C_INST_ID_2,
};

static Bsp_BoardDeviceData  gBoardTI814xVcDevData[] =
    BSP_BOARD_TI814X_VC_DEVDATA;

static Bsp_BoardDeviceData  gBoardTI814xVisionTI81xxDevData[] =
    BSP_BOARD_TI814X_VISION_DEVDATA;

static Bsp_BoardDeviceData  gBoardTI814xVsDevData[] =
    BSP_BOARD_TI814X_VS_DEVDATA;

static Bsp_BoardDeviceData  gBoardTI814xCatalogDevData[] =
    BSP_BOARD_TI814X_CATALOG_DEVDATA;

static Bsp_BoardData        gBoardTI814xVcData =
{
    /* numDev */
    (sizeof (gBoardTI814xVcDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTI814xVcDevData,
};

static Bsp_BoardData        gBoardTI814xVisionTI81xxData =
{
    /* numDev */
    (sizeof (gBoardTI814xVisionTI81xxDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTI814xVisionTI81xxDevData,
};

static Bsp_BoardData        gBoardTI814xVsData =
{
    /* numDev */
    (sizeof (gBoardTI814xVsDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTI814xVsDevData,
};

static Bsp_BoardData        gBoardTI814xCatalogData =
{
    /* numDev */
    (sizeof (gBoardTI814xCatalogDevData) / sizeof (Bsp_BoardDeviceData)),
    /* devData */
    gBoardTI814xCatalogDevData,
};

static Bsp_BoardData        gBoardTI814xCustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

static Bsp_BoardData        gBoardTI814xDefaultData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

extern Bsp_BoardData        gBoardTda2xxVisionData;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Bsp_BoardId Bsp_boardGetIdTI814x(void)
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
        boardId = BSP_BOARD_VC;
    }
    else
    {
        /*
         * Detect board ID
         */

        /* TVP5158 is present in VS board */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            (UInt8) BOARD_TVP5158_I2C_ADDR_0);
        if (FVID2_SOK == retVal)
        {
            boardId = BSP_BOARD_VS;
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * Probe for SII9127 @ 0x31 address to detect
             * Vision daughter card.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                (UInt8) BOARD_SII9127_I2C_ADDR_1);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_VISION;
            }
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * Probe for TVP5158 @ 0x5F address to detect
             * Vision daughter card of TI81XX.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                (UInt8) BOARD_TVP5158_I2C_ADDR_7);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_VISION_TI81XX;
            }
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * Since TVP5158 was not detected probe for SII9135 or TVP7002
             * to detect VC and Catalog daughter card.
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                (UInt8) BOARD_SII9135_I2C_ADDR_0);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_VC;
            }
        }

        if (FVID2_SOK != retVal)
        {
            /*
             * TI814x Catalog board
             * TVP7002 I2C2 0x5D   -   VIN 0
             * SIL1161 I2C2 0x76   -   VIN 0 TVP7002 and SIL1161 are mutually
             *                         exclusive
             * PCF8575 I2C2 0x21   -   IO Expander to reset / select TVP7002
             * TVP5147 I2C2 0xB8
             */
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                (UInt8) BOARD_TVP7002_I2C_ADDR_0);
            if (FVID2_SOK == retVal)
            {
                boardId = BSP_BOARD_CATALOG;
            }
        }
    }

    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevTI814x(void)
{
    /* Only one revision of board till date */
    return (BSP_BOARD_REV_A);
}

Bsp_BoardRev Bsp_boardGetDcRevTI814x(void)
{
    Int32        retVal;
    Bsp_BoardId  boardId;
    Bsp_BoardRev dcBoardRev = BSP_BOARD_REV_UNKNOWN;
    const Bsp_BoardI2cData *i2cData;

    boardId = Bsp_boardGetId();
    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if (BSP_BOARD_VC == boardId)
    {
        /* Relies on I2C Address of IO Expander.
         * REV A IO Expander is at 0x27 and REV B IO Expander at 0x21 */
        retVal = Bsp_deviceI2cProbeDevice(
            i2cData->probeInstId,
            (UInt8) BOARD_IO_EXP_I2C_ADDR_7);
        if (FVID2_SOK == retVal)
        {
            dcBoardRev = BSP_BOARD_REV_A;
        }
        else
        {
            retVal = Bsp_deviceI2cProbeDevice(
                i2cData->probeInstId,
                (UInt8) BOARD_IO_EXP_I2C_ADDR_1);
            if (FVID2_SOK == retVal)
            {
                dcBoardRev = BSP_BOARD_REV_B;
            }
        }
    }
    else
    {
        /* Only one revision of board till date for other cards */
        dcBoardRev = BSP_BOARD_REV_A;
    }

    return (dcBoardRev);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cDataTI814x(void)
{
    return (&gBoardTI814xI2cData);
}

const Bsp_BoardData *Bsp_boardGetDataTI814x(void)
{
    Bsp_BoardId          boardId;
    const Bsp_BoardData *boardData = NULL;

    boardId = Bsp_boardGetId();
    switch (boardId)
    {
        case BSP_BOARD_VS:
            boardData = &gBoardTI814xVsData;
            break;

        case BSP_BOARD_VC:
            boardData = &gBoardTI814xVcData;
            break;

        case BSP_BOARD_VISION:
            boardData = &gBoardTda2xxVisionData;
            break;

        case BSP_BOARD_VISION_TI81XX:
            boardData = &gBoardTI814xVisionTI81xxData;
            break;

        case BSP_BOARD_CATALOG:
            boardData = &gBoardTI814xCatalogData;
            break;

        case BSP_BOARD_CUSTOM:
            boardData = &gBoardTI814xCustomData;
            break;

        case BSP_BOARD_UNKNOWN:
        default:
            boardData = &gBoardTI814xDefaultData;
            break;
    }

    return (boardData);
}

static Int32 Bsp_boardSelectDeviceTI814xVc(UInt32 devDrvId, UInt32 instId)
{
    Int32 retVal = BSP_SOK;

    if (FVID2_VID_DEC_SII9135_DRV == devDrvId)
    {
        /* GMII1 and SII9135A are muxed on TI814x VC card */
        /* TODO */
    }

    return (retVal);
}

static Int32 Bsp_boardSelectDeviceTI814xCatlog(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs;
    const Bsp_BoardI2cData *i2cData;
    UInt32 regValueTmp;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));
    i2cInst = i2cData->probeInstId;

    if (FVID2_VID_DEC_TVP7002_DRV == devDrvId)
    {
        ioExpAddr = BOARD_IO_EXP_I2C_ADDR_1;
        numRegs   = 2U;
        retVal    = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C read failed!!\n");
        }

        /* Configure muxes to select TVP */
        regValueTmp =
            ((UInt32) regValue[1U] | ((UInt32) BOARD_PCF8575_SEL_TVP_S0_MASK));
        regValue[1U] = (UInt8) regValueTmp;
        regValueTmp  =
            ((UInt32) regValue[1U] & (UInt32) ~((UInt32) PCF8575_P1_7_MASK));
        regValue[1U] = (UInt8) regValueTmp;

        retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
        }
    }

    return (retVal);
}

static Int32 Bsp_boardSelectDeviceTI814xVisionTI81xx(UInt32 devDrvId,
                                                     UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt8  regValue[2];
    UInt32 i2cInst, ioExpAddr, numRegs, delay;
    const Bsp_BoardI2cData *i2cData;

    i2cData = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));
    i2cInst = i2cData->probeInstId;

    /* Do special enable for VISION board */
    Bsp_boardEnableVisionBoardTI814x();

    if (FVID2_VID_SENSOR_MT9V022_DRV == devDrvId)
    {
        /* Configure the I2C switch PCA9543 */
        ioExpAddr    = BOARD_PCA9543_I2C_ADDR;
        regValue[0U] = 0x03U;

        /* writing a value 3 to the PCA9543 enables both I2C channels */
        numRegs = 1U;
        retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
        }

        delay = 100U;
        BspOsal_sleep(delay);

        /* writing a value 3 to the PCA9543 enables both I2C channels */
        retVal += Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspBoardTrace, GT_ERR, "I2C write failed!!\n");
        }
    }

    return (retVal);
}

static void Bsp_boardEnableVisionBoardTI814x(void)
{
    volatile UInt32 regValue;
    volatile UInt32 gpIOClk;

    /* Enable GPI1 System and Functional Clock*/
    HW_WR_REG32(CM_ALWON_GPIO_1_CLKCTRL_REG, 0x2);

    /* Poll till Module is functional*/
    gpIOClk = HW_RD_REG32(CM_ALWON_GPIO_1_CLKCTRL_REG);
    while (gpIOClk != 0x2U)
    {
        gpIOClk = HW_RD_REG32(CM_ALWON_GPIO_1_CLKCTRL_REG);
        /* wait */
    }

    /* Pull-down NOR_ENABLE */
    /* GP1[21] is selected :: Function #7 */
    HW_WR_REG32(PINCNTL115, 0x00020080U);

    /* Enable bit/port 21 of GPIO-1 OUTPUT ENABLE register. */
    regValue = HW_RD_REG32(GPIO_1_OUTPUT_ENABLE);
    regValue = (regValue & ~((UInt32) 1U << ENABLE_GPIO));
    HW_WR_REG32(GPIO_1_OUTPUT_ENABLE, regValue);

    /* Enable bit/port 21 of GPIO-1 DATA OUTPUT register. */
    regValue = HW_RD_REG32(GPIO_1_DATA_OUTPUT);
    regValue = (regValue | ((UInt32) 1U << ENABLE_GPIO));
    HW_WR_REG32(GPIO_1_DATA_OUTPUT, regValue);

    /* Enable bit/port 21 of GPIO-1 SET DATA OUTPUT register. */
    regValue = HW_RD_REG32(GPIO_1_SET_DATA_OUTPUT);
    regValue = (regValue | ((UInt32) 1U << ENABLE_GPIO));
    HW_WR_REG32(GPIO_1_SET_DATA_OUTPUT, regValue);

    return;
}

