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
 *  \file stw_boardTI814x.c
 *
 *  \brief File containing the TI814x STW board functions.
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
#include <ti814x/soc_defines.h>
#include <gpio_v2.h>
#include <platforms/stw_platform.h>
#include "soc.h"
#include "i2clib/lld_hsi2c.h"
#include <devices/stw_device.h>
#include <boards/stw_board.h>
#include <stw_boardPriv.h>
#include <stw_boardTI814xCatalog.h>
#include <stw_boardTI814xVc.h>
#include <stw_boardTI814xVision.h>
#include <stw_boardTI814xVs.h>
#include <common/stw_utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Uncomment below macro to enable I2C0 initialization. */
#define STW_BOARD_ENABLE_I2C0

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
#if 0 /* Todo */
static void BOARDEnableVisionBoardTI814x(void);
static int32_t BOARDSelectDeviceTI814xCatlog(uint32_t devDrvId, uint32_t instId);
static int32_t BOARDSelectDeviceTI814xVc(uint32_t devDrvId, uint32_t instId);
static int32_t BOARDSelectDeviceTI814xVisionTI81xx(uint32_t devDrvId,
                                                   uint32_t instId);
#endif
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static boardI2cInstData_t gBoardTI814xI2cInstData[] =
{
#ifndef STW_DISABLE_I2C0
    {
        HSI2C_INST_0,                       /* instId */
        CSL_I2C0_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT0,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    },
#endif
#ifdef TI814X_FAMILY_BUILD
    {
        HSI2C_INST_2,                       /* instId */
        CSL_I2C2_BASE,                      /* baseAddr */
        CSL_INTC_EVENTID_I2CINT2,           /* intNum */
        I2C_NORMAL                          /* busClkKHz */
    }
#endif
};

static boardI2cData_t     gBoardTI814xI2cData =
{
    /* numI2c */
    (sizeof (gBoardTI814xI2cInstData) / sizeof (boardI2cInstData_t)),
    /* i2cData */
    gBoardTI814xI2cInstData,
    /* probeInstId */
#ifdef TI814X_FAMILY_BUILD
    HSI2C_INST_2,
#else
    HSI2C_INST_MAX,
#endif
};

static boardDeviceData_t  gBoardTI814xVcDevData[] =
    BOARD_TI814X_VC_DEVDATA;
#if 0 /* Todo */
static boardDeviceData_t  gBoardTI814xVisionTI81xxDevData[] =
    BOARD_TI814X_VISION_DEVDATA;

static boardDeviceData_t  gBoardTI814xVsDevData[] =
    BOARD_TI814X_VS_DEVDATA;

static boardDeviceData_t  gBoardTI814xCatalogDevData[] =
    BOARD_TI814X_CATALOG_DEVDATA;
#endif
static boardData_t        gBoardTI814xVcData =
{
    /* numDev */
    (sizeof (gBoardTI814xVcDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTI814xVcDevData,
    /* pinMuxdata */
    NULL
};
#if 0 /* Todo */
static boardData_t        gBoardTI814xVisionTI81xxData =
{
    /* numDev */
    (sizeof (gBoardTI814xVisionTI81xxDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTI814xVisionTI81xxDevData,
    /* pinMuxdata */
    NULL
};

static boardData_t        gBoardTI814xVsData =
{
    /* numDev */
    (sizeof (gBoardTI814xVsDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTI814xVsDevData,
    /* pinMuxdata */
    NULL
};

static boardData_t        gBoardTI814xCatalogData =
{
    /* numDev */
    (sizeof (gBoardTI814xCatalogDevData) / sizeof (boardDeviceData_t)),
    /* devData */
    gBoardTI814xCatalogDevData,
    /* pinMuxdata */
    NULL
};

static boardData_t        gBoardTI814xCustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
    NULL                                    /* pinMuxdata */
};

static boardData_t        gBoardTI814xDefaultData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
    NULL                                    /* pinMuxdata */
};
#endif
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t BOARDTI814xInit(boardInitParams_t *pInitPrms)
{
    return (STW_SOK);
}

boardId_t BOARDGetIdTI814x(void)
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
            boardId = BOARD_VC;
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
                BOARD_TVP5158_I2C_ADDR_0);
            if (LLD_HSI2C_SUCCESS == retVal)
            {
                boardId = BOARD_VS;
            }

            if (LLD_HSI2C_SUCCESS != retVal)
            {
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
            }

            if (LLD_HSI2C_SUCCESS != retVal)
            {
                /*
                 * Probe for TVP5158 @ 0x5F address to detect
                 * Vision daughter card of TI81XX.
                 */
                retVal = DEVICEI2cProbeDevice(
                    i2cData->probeInstId,
                    BOARD_TVP5158_I2C_ADDR_7);
                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    boardId = BOARD_VISION_TI81XX;
                }
            }

            if (LLD_HSI2C_SUCCESS != retVal)
            {
                /*
                 * Since TVP5158 was not detected probe for SII9135 or TVP7002
                 * to detect VC and Catalog daughter card.
                 */
                retVal = DEVICEI2cProbeDevice(
                    i2cData->probeInstId,
                    BOARD_SII9135_I2C_ADDR_0);
                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    boardId = BOARD_VC;
                }
            }

            if (LLD_HSI2C_SUCCESS != retVal)
            {
                /*
                 * TI814x Catalog board
                 * TVP7002 I2C2 0x5D   -   VIN 0
                 * SIL1161 I2C2 0x76   -   VIN 0 TVP7002 and SIL1161 are
                 * mutually exclusive
                 * PCF8575 I2C2 0x21   -   IO Expander to reset / select TVP7002
                 * TVP5147 I2C2 0xB8
                 */
                retVal = DEVICEI2cProbeDevice(
                    i2cData->probeInstId,
                    BOARD_TVP7002_I2C_ADDR_0);
                if (LLD_HSI2C_SUCCESS == retVal)
                {
                    boardId = BOARD_CATALOG;
                }
            }
        }
    }
    else
    {
        console_print_string(" \r\nNULL Pointer Detected i2cData : ");
    }
    return (boardId);
}

boardRev_t BOARDGetBaseBoardRevTI814x(void)
{
    /* Only one revision of board till date */
    return (BOARD_REV_A);
}

boardRev_t BOARDGetDcRevTI814x(void)
{
    /* TBD */
    return (BOARD_REV_A);
}

const boardI2cData_t *BOARDGetI2cDataTI814x(void)
{
    /* TBD */
    return (&gBoardTI814xI2cData);
}

const boardData_t *BOARDGetDataTI814x(void)
{
    boardData_t *boardDat;

    boardDat = &gBoardTI814xVcData;

    /* TBD */
    return (boardDat);
}

#if 0 /* TBD */
static int32_t BOARDSelectDeviceTI814xVc(uint32_t devDrvId, uint32_t instId)
{
    /* TBD */
    return (STW_SOK);
}

static int32_t BOARDSelectDeviceTI814xCatlog(uint32_t devDrvId, uint32_t instId)
{
    /* TBD */
    return (STW_SOK);
}

static int32_t BOARDSelectDeviceTI814xVision(uint32_t devDrvId, uint32_t instId)
{
    /* TBD */
    return (STW_SOK);
}

static void BOARDEnableVisionBoardTI814x(void)
{
    /* TBD */
    return;
}

#endif
