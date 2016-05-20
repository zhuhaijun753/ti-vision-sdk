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
 *  \file bsp_board.c
 *
 *  \brief File containing the BSP board functions.
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
#include <platforms/bsp_platform.h>
#include <devices/bsp_device.h>
#include <boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <hw_types.h>
#include <soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Bsp_BoardId          boardId;
    /**< Board ID. For valid values see #Bsp_BoardId. */
    Bsp_BoardRev         baseBoardRev;
    /**< Base Board revision. */
    Bsp_BoardRev         dcBoardRev;
    /**< Daughter card board revision. */
    Bsp_BoardCustomData *customData;
    /**< Pointer to custom board data structure. */
    BspOsal_SemHandle    lock;
    /**< Generic lock for task re-entrant protection. */
} Bsp_BoardCommonObj;

/**
 *  struct Bsp_BoardIdString
 *  \brief Structure to store board ID and string pair.
 */
typedef struct
{
    Bsp_BoardId boardId;
    /**< Board ID. */
    const Char *boardIdStr;
    /**< Pointer to board ID string. */
} Bsp_BoardIdString;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 Bsp_boardEnableThs7353(Fvid2_Standard standard,
                                    UInt32         i2cInstId,
                                    UInt32         i2cDevAddr);
static Int32 Bsp_boardEnableThs73681(Fvid2_Standard standard,
                                     UInt32         i2cInst,
                                     UInt32         ioExpAddr);
static Int32 Bsp_boardLock(void);
static Int32 Bsp_boardUnlock(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardCommonObj gBoardCommonObj;

static Bsp_BoardIdString  gBoardIdStrTable[] =
{
    {BSP_BOARD_UNKNOWN,       "UNKNOWN"       },
    {BSP_BOARD_VS,            "VS"            },
    {BSP_BOARD_MONSTERCAM,    "MONSTER_CAM"   },
    {BSP_BOARD_VC,            "VC"            },
    {BSP_BOARD_VISION,        "Vision"        },
    {BSP_BOARD_VISION_TI81XX, "Vision(TI81XX)"},
    {BSP_BOARD_CATALOG,       "Catalog"       },
    {BSP_BOARD_CUSTOM,        "Custom"        },
    {BSP_BOARD_JAMR3,         "JAMR3"         },
    {BSP_BOARD_MULTIDES,      "MULTIDES"      },
    {BSP_BOARD_BASE_TDA2XX,   "TDA2XX BASE"   },
    {BSP_BOARD_BASE_TDA3XX,   "TDA3XX BASE"   },
    {BSP_BOARD_BASE_TI81XX,   "TI81XX BASE"   },
    {BSP_BOARD_BASE_TDA2EX,   "TDA2EX BASE"   },
};

static Char *gBoardRevStr[] =
{
    "UNKNOWN",
    "REV A",
    "REV B",
    "REV C",
    "REV D",
    "REV E",
};

/** \brief Number of entries in board ID string table. */
#define BSP_BOARD_NUM_ID_STR_ENTRIES        (sizeof (gBoardIdStrTable) / \
                                             sizeof (Bsp_BoardIdString))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_boardInit(const Bsp_BoardInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    Int32 initValue;
    Bsp_BoardInitParams localInitPrms;

    BspUtils_memset(&gBoardCommonObj, 0, sizeof (gBoardCommonObj));

    /* If NULL is passed pinMux will be initialized by default */
    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        BspBoardInitParams_init(&localInitPrms);
    }

    gBoardCommonObj.boardId      = initPrms->boardId;
    gBoardCommonObj.baseBoardRev = initPrms->baseBoardRev;
    gBoardCommonObj.dcBoardRev   = initPrms->dcBoardRev;
    gBoardCommonObj.customData   = initPrms->customData;
    if (NULL != gBoardCommonObj.customData)
    {
        /* Below parameters can't be NULL */
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->boardIdString != NULL));
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->boardRevString != NULL));
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->i2cData != NULL));
        GT_assert(BspBoardTrace,
                  (gBoardCommonObj.customData->boardData != NULL));
    }

    /* Create global board lock */
    initValue = (Int32) 1;
    gBoardCommonObj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBoardCommonObj.lock)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "Global semaphore create failed\n");
        retVal = BSP_EALLOC;
    }

    /* Macro is used insted of Bsp_platformIsTda2xxFamilyBuild. Any Platform API
     * cannot be called in board init as platform init happens after board
     * init */
    if (BSP_SOK == retVal)
    {
        if (NULL != gBoardCommonObj.customData)
        {
            if (NULL != gBoardCommonObj.customData->initFxn)
            {
                retVal = gBoardCommonObj.customData->initFxn();
            }
        }
        else
        {
            /* Use default built-in board functions */
#ifdef TDA2XX_FAMILY_BUILD
  #ifdef TDA2EX_BUILD
            retVal = Bsp_boardTda2exInit();
  #else
            retVal = Bsp_boardTda2xxInit();
  #endif
#endif

#ifdef TDA3XX_FAMILY_BUILD
            retVal = Bsp_boardTda3xxInit();
#endif
        }
    }

    return (retVal);
}

Int32 Bsp_boardDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBoardCommonObj.lock);

    return (retVal);
}

Bsp_BoardId Bsp_boardGetId(void)
{
    if (BSP_BOARD_MAX == gBoardCommonObj.boardId)
    {
        if (Bsp_platformGetId() != BSP_PLATFORM_ID_EVM)
        {
            gBoardCommonObj.boardId = BSP_BOARD_UNKNOWN;
        }
        else
        {
            if (Bsp_platformIsTda2xxFamilyBuild())
            {
                if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
                {
                    gBoardCommonObj.boardId = Bsp_boardGetIdTda2ex();
                }
                else
                {
                    gBoardCommonObj.boardId = Bsp_boardGetIdTda2xx();
                }
            }

            if (Bsp_platformIsTda3xxFamilyBuild())
            {
                gBoardCommonObj.boardId = Bsp_boardGetIdTda3xx();
            }

            if (Bsp_platformIsTI814xFamilyBuild())
            {
                gBoardCommonObj.boardId = Bsp_boardGetIdTI814x();
            }

            if (Bsp_platformIsOmap5xFamilyBuild())
            {
                gBoardCommonObj.boardId = Bsp_boardGetIdOmap5430();
            }
        }
    }

    return (gBoardCommonObj.boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRev(void)
{
    if (BSP_BOARD_REV_MAX == gBoardCommonObj.baseBoardRev)
    {
        if (Bsp_platformGetId() != BSP_PLATFORM_ID_EVM)
        {
            gBoardCommonObj.baseBoardRev = BSP_BOARD_REV_A;
        }
        else
        {
            if (Bsp_platformIsTda2xxFamilyBuild())
            {
                if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
                {
                    gBoardCommonObj.baseBoardRev =
                        Bsp_boardGetBaseBoardRevTda2ex();
                }
                else
                {
                    gBoardCommonObj.baseBoardRev =
                        Bsp_boardGetBaseBoardRevTda2xx();
                }
            }

            if (Bsp_platformIsTda3xxFamilyBuild())
            {
                gBoardCommonObj.baseBoardRev =
                    Bsp_boardGetBaseBoardRevTda3xx();
            }

            if (Bsp_platformIsTI814xFamilyBuild())
            {
                gBoardCommonObj.baseBoardRev = Bsp_boardGetBaseBoardRevTI814x();
            }

            if (Bsp_platformIsOmap5xFamilyBuild())
            {
                gBoardCommonObj.baseBoardRev =
                    Bsp_boardGetBaseBoardRevOmap5430();
            }
        }
    }

    return (gBoardCommonObj.baseBoardRev);
}

Bsp_BoardRev Bsp_boardGetDcRev(void)
{
    if (BSP_BOARD_REV_MAX == gBoardCommonObj.dcBoardRev)
    {
        if (Bsp_platformIsTda2xxFamilyBuild())
        {
            if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
            {
                gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTda2ex();
            }
            else
            {
                gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTda2xx();
            }
        }

        if (Bsp_platformIsTda3xxFamilyBuild())
        {
            gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTda3xx();
        }

        if (Bsp_platformIsTI814xFamilyBuild())
        {
            gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevTI814x();
        }

        if (Bsp_platformIsOmap5xFamilyBuild())
        {
            gBoardCommonObj.dcBoardRev = Bsp_boardGetDcRevOmap5430();
        }
    }

    return (gBoardCommonObj.dcBoardRev);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cData(void)
{
    const Bsp_BoardI2cData *i2cData = NULL;

    if (Bsp_platformIsTda2xxFamilyBuild())
    {
        if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
        {
            i2cData = Bsp_boardGetI2cDataTda2ex();
        }
        else
        {
            i2cData = Bsp_boardGetI2cDataTda2xx();
        }
    }

    if (Bsp_platformIsTda3xxFamilyBuild())
    {
        i2cData = Bsp_boardGetI2cDataTda3xx();
    }

    if (Bsp_platformIsOmap5xFamilyBuild())
    {
        i2cData = Bsp_boardGetI2cDataOmap5430();
    }

    if (Bsp_platformIsTI814xFamilyBuild())
    {
        i2cData = Bsp_boardGetI2cDataTI814x();
    }

    return (i2cData);
}

const Bsp_BoardData *Bsp_boardGetData(void)
{
    const Bsp_BoardData *boardData = NULL;

    if (NULL != gBoardCommonObj.customData)
    {
        boardData = gBoardCommonObj.customData->boardData;
    }
    else
    {
        if (Bsp_platformIsTda2xxFamilyBuild())
        {
            if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
            {
                boardData = Bsp_boardGetDataTda2ex();
            }
            else
            {
                boardData = Bsp_boardGetDataTda2xx();
            }
        }

        if (Bsp_platformIsTda3xxFamilyBuild())
        {
            boardData = Bsp_boardGetDataTda3xx();
        }

        if (Bsp_platformIsTI814xFamilyBuild())
        {
            boardData = Bsp_boardGetDataTI814x();
        }

        if (Bsp_platformIsOmap5xFamilyBuild())
        {
            boardData = Bsp_boardGetDataOmap5430();
        }
    }

    return (boardData);
}

UInt32 Bsp_boardGetVideoDeviceInstId(UInt32 devDrvId,
                                     UInt32 drvId,
                                     UInt32 drvInstId)
{
    UInt32 instId = BSP_BOARD_INVALID_INST_ID;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->drvId == drvId) &&
            (devData->drvInstId == drvInstId))
        {
            instId = devData->instId;
            break;
        }
    }

    if (BSP_BOARD_INVALID_INST_ID == instId)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "Invalid device driver ID!!\n");
    }

    return (instId);
}

UInt32 Bsp_boardGetVideoDeviceI2cInstId(UInt32 devDrvId,
                                        UInt32 drvId,
                                        UInt32 drvInstId)
{
    UInt32 i2cInstId = BSP_DEVICE_I2C_INST_ID_MAX;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->drvId == drvId) &&
            (devData->drvInstId == drvInstId))
        {
            i2cInstId = devData->i2cInstId;
            break;
        }
    }

    if (BSP_DEVICE_I2C_INST_ID_MAX == i2cInstId)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "Invalid device driver ID!!\n");
    }

    return (i2cInstId);
}

UInt32 Bsp_boardGetVideoDeviceI2cAddr(UInt32 devDrvId,
                                      UInt32 drvId,
                                      UInt32 drvInstId)
{
    UInt32 i2cAddr = 0U;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->drvId == drvId) &&
            (devData->drvInstId == drvInstId))
        {
            i2cAddr = devData->i2cAddr;
            break;
        }
    }

    if (0U == i2cAddr)
    {
        GT_0trace(BspBoardTrace, GT_ERR, "Invalid device driver ID!!\n");
    }

    return (i2cAddr);
}

Int32 Bsp_boardPowerOnDevice(UInt32 devDrvId, UInt32 instId, UInt32 powerOn)
{
    Int32  retVal = BSP_SOK;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    Bsp_boardLock();

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->instId == instId) &&
            (devData->powerOnDev != NULL))
        {
            retVal = devData->powerOnDev(devDrvId, instId, powerOn);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "Device power-on failed!!\n");
            }
            break;
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardSelectDevice(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    Bsp_boardLock();

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->instId == instId) &&
            (devData->selectDev != NULL))
        {
            retVal = devData->selectDev(devDrvId, instId);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "Device select failed!!\n");
            }
            break;
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardResetDevice(UInt32 devDrvId, UInt32 instId)
{
    Int32  retVal = BSP_SOK;
    UInt32 devCnt;
    const Bsp_BoardData *boardData;
    const Bsp_BoardDeviceData *devData;

    boardData = Bsp_boardGetData();
    GT_assert(BspBoardTrace, (boardData != NULL));

    Bsp_boardLock();

    for (devCnt = 0U; devCnt < boardData->numDev; devCnt++)
    {
        GT_assert(BspBoardTrace, (boardData->devData != NULL));
        devData = &boardData->devData[devCnt];
        if ((devData->devDrvId == devDrvId) &&
            (devData->instId == instId) &&
            (devData->resetDev != NULL))
        {
            retVal = devData->resetDev(devDrvId, instId);
            if (BSP_SOK != retVal)
            {
                GT_0trace(BspBoardTrace, GT_ERR, "Device reset failed!!\n");
            }
            break;
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardSelectMode(UInt32        devDrvId,
                          UInt32        instId,
                          Bsp_BoardMode boardMode)
{
    Int32 retVal = BSP_SOK;

    Bsp_boardLock();

    if (NULL != gBoardCommonObj.customData)
    {
        if (NULL != gBoardCommonObj.customData->selectModeFxn)
        {
            retVal = gBoardCommonObj.customData->selectModeFxn(devDrvId,
                                                               instId,
                                                               boardMode);
        }
    }
    else
    {
        if (Bsp_platformIsTda2xxFamilyBuild())
        {
#if defined (TDA3XX_INTERPOSER_BUILD)
            retVal = Bsp_boardSelectModeTda3xx(devDrvId, instId, boardMode);
#endif
        }

        if (Bsp_platformIsTda3xxFamilyBuild())
        {
            retVal = Bsp_boardSelectModeTda3xx(devDrvId, instId, boardMode);
        }
    }

    Bsp_boardUnlock();

    return (retVal);
}

Int32 Bsp_boardEnableTvp7002Filter(UInt32 instId, Fvid2_Standard standard)
{
    Int32        retVal = BSP_SOK;
    Bsp_BoardId  boardId;
    Bsp_BoardRev dcBoardRev;
    const Bsp_BoardI2cData *i2cData;

    boardId    = Bsp_boardGetId();
    dcBoardRev = Bsp_boardGetDcRev();
    i2cData    = Bsp_boardGetI2cData();
    GT_assert(BspBoardTrace, (i2cData != NULL));

    if (BSP_BOARD_VC == boardId)
    {
        if (BSP_BOARD_REV_A == dcBoardRev)
        {
            retVal = Bsp_boardEnableThs7353(
                standard,
                i2cData->probeInstId,
                (UInt32) BOARD_THS7353_I2C_ADDR);
        }
        else if (BSP_BOARD_REV_B == dcBoardRev)
        {
            retVal = Bsp_boardEnableThs73681(
                standard,
                i2cData->probeInstId,
                (UInt32) BOARD_IO_EXP_I2C_ADDR_1);
        }
        else
        {
            GT_0trace(BspBoardTrace, GT_ERR, "Invalid DC revision!!\n");
            retVal = BSP_EFAIL;
        }
    }
    else if (BSP_BOARD_CATALOG == boardId)
    {
        retVal = Bsp_boardEnableThs73681(
            standard,
            i2cData->probeInstId,
            (UInt32) BOARD_IO_EXP_I2C_ADDR_1);
    }
    else
    {
        /* Do nothing for other boards */
    }

    return (retVal);
}

const Char *Bsp_boardGetBoardString(void)
{
    UInt32      entryCnt;
    const Char *boardIdStr = NULL;
    Bsp_BoardId boardId;

    if (NULL != gBoardCommonObj.customData)
    {
        boardIdStr = gBoardCommonObj.customData->boardIdString;
    }
    else
    {
        boardId = Bsp_boardGetId();
        if (boardId >= BSP_BOARD_MAX)
        {
            boardId = BSP_BOARD_UNKNOWN;
        }

        for (entryCnt = 0U; entryCnt < BSP_BOARD_NUM_ID_STR_ENTRIES; entryCnt++)
        {
            if (gBoardIdStrTable[entryCnt].boardId == boardId)
            {
                boardIdStr = gBoardIdStrTable[entryCnt].boardIdStr;
                break;
            }
        }
    }
    GT_assert(BspBoardTrace, (boardIdStr != NULL));

    return (boardIdStr);
}

Int32 Bsp_boardSetPinMux(UInt32        drvId,
                         UInt32        instId,
                         Bsp_BoardMode boardMode)
{
    Int32 status = FVID2_SOK;

    if (NULL != gBoardCommonObj.customData)
    {
        if (NULL != gBoardCommonObj.customData->setPinMuxFxn)
        {
            gBoardCommonObj.customData->setPinMuxFxn(drvId, instId, boardMode);
        }
    }
    else
    {
        if (Bsp_platformIsTda2xxFamilyBuild())
        {
            if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
            {
                Bsp_boardSetPinMuxTda2ex(drvId, instId, boardMode);
            }
            else
            {
                Bsp_boardSetPinMuxTda2xx(drvId, instId, boardMode);
            }
        }

        if (Bsp_platformIsTda3xxFamilyBuild())
        {
            Bsp_boardSetPinMuxTda3xx(drvId, instId, boardMode);
        }
    }

    return (status);
}

const Char *Bsp_boardGetBaseBoardRevString(void)
{
    Bsp_BoardRev boardRev;
    const Char  *boardRevStr = NULL;

    if (NULL != gBoardCommonObj.customData)
    {
        boardRevStr = gBoardCommonObj.customData->boardRevString;
    }
    else
    {
        /* Check for out of bound access */
        GT_assert(BspBoardTrace,
                  (BSP_BOARD_REV_MAX ==
                   ((sizeof (gBoardRevStr)) / (sizeof (Char *)))));

        boardRev = Bsp_boardGetBaseBoardRev();
        if (boardRev >= BSP_BOARD_REV_MAX)
        {
            boardRev = BSP_BOARD_REV_UNKNOWN;
        }
        boardRevStr = gBoardRevStr[boardRev];
    }

    return (boardRevStr);
}

const Char *Bsp_boardGetDcRevString(void)
{
    Bsp_BoardRev boardRev;

    /* Check for out of bound access */
    GT_assert(BspBoardTrace,
              (BSP_BOARD_REV_MAX ==
               ((sizeof (gBoardRevStr)) / (sizeof (Char *)))));

    boardRev = Bsp_boardGetDcRev();
    if (boardRev >= BSP_BOARD_REV_MAX)
    {
        boardRev = BSP_BOARD_REV_UNKNOWN;
    }

    return (gBoardRevStr[boardRev]);
}

void Bsp_boardPrintInfo(void)
{
    GT_1trace(BspBoardTrace, GT_INFO,
              " Board Detected        : [%s]\r\n", Bsp_boardGetBoardString());
    GT_1trace(BspBoardTrace, GT_INFO,
              " Base Board Revision   : [%s]\r\n",
              Bsp_boardGetBaseBoardRevString());
    GT_1trace(BspBoardTrace, GT_INFO,
              " Daughter Card Revision: [%s]\r\n", Bsp_boardGetDcRevString());

    return;
}

static Int32 Bsp_boardEnableThs7353(Fvid2_Standard standard,
                                    UInt32         i2cInstId,
                                    UInt32         i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt8  regAddr, regValue;
    UInt32 numRegs;

    switch (standard)
    {
        case FVID2_STD_1080P_60:
        case FVID2_STD_1080P_50:
        case FVID2_STD_SXGA_60:
        case FVID2_STD_SXGA_75:
        case FVID2_STD_SXGAP_60:
        case FVID2_STD_SXGAP_75:
        case FVID2_STD_UXGA_60:
            regValue = (UInt8) 0x9CU;
            break;

        case FVID2_STD_1080I_60:
        case FVID2_STD_1080I_50:
        case FVID2_STD_1080P_24:
        case FVID2_STD_1080P_30:
        case FVID2_STD_720P_60:
        case FVID2_STD_720P_50:
        case FVID2_STD_SVGA_60:
        case FVID2_STD_SVGA_72:
        case FVID2_STD_SVGA_75:
        case FVID2_STD_SVGA_85:
        case FVID2_STD_XGA_60:
        case FVID2_STD_XGA_DSS_TDM_60:
        case FVID2_STD_XGA_70:
        case FVID2_STD_XGA_75:
        case FVID2_STD_XGA_85:
        case FVID2_STD_WXGA_60:
        case FVID2_STD_WXGA_75:
        case FVID2_STD_WXGA_85:
            regValue = (UInt8) 0x94U;
            break;

        case FVID2_STD_480P:
        case FVID2_STD_576P:
        case FVID2_STD_VGA_60:
        case FVID2_STD_VGA_72:
        case FVID2_STD_VGA_75:
        case FVID2_STD_VGA_85:
            regValue = (UInt8) 0x4CU;
            break;

        case FVID2_STD_NTSC:
        case FVID2_STD_PAL:
        case FVID2_STD_480I:
        case FVID2_STD_576I:
        case FVID2_STD_D1:
            regValue = (UInt8) 0x04U;
            break;

        default:
            regValue = (UInt8) 0x94U;
            break;
    }

    regAddr = (UInt8) 0x01U;
    numRegs = 1U;
    retVal += Bsp_deviceWrite8(i2cInstId, i2cDevAddr, &regAddr, &regValue,
                               numRegs);
    regAddr = (UInt8) 0x02U;
    retVal += Bsp_deviceWrite8(i2cInstId, i2cDevAddr, &regAddr, &regValue,
                               numRegs);
    regAddr = (UInt8) 0x03U;
    retVal += Bsp_deviceWrite8(i2cInstId, i2cDevAddr, &regAddr, &regValue,
                               numRegs);

    return (retVal);
}

/* Used for TI814x VC REV B card only */
static Int32 Bsp_boardEnableThs73681(Fvid2_Standard standard,
                                     UInt32         i2cInst,
                                     UInt32         ioExpAddr)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regValue[2];
    UInt32 numRegs;
    UInt32 regValueTemp;

    numRegs = 2U;
    retVal  = Bsp_deviceRawRead8(i2cInst, ioExpAddr, regValue, numRegs);
    GT_assert(BspBoardTrace, (retVal == FVID2_SOK));

    /*  PCF8575 - mappings
     *  P7 - THS73861_FILTER2
     *  P6 - THS73861_FILTER1
     *  P5 - THS73861_BYPASS
     *  P4 - THS73861_DISABLE
     *  P0 - TVP7002_RSTN */
    /* Enable filter, disable bypass, clear filter select bits */
    regValueTemp =
        ((UInt32) regValue[0] & ((UInt32) ~(BOARD_PCF8575_THS73861_DISABLE_MASK
                                            |
                                            BOARD_PCF8575_THS73861_BYPASS_MASK
                                            |
                                            BOARD_PCF8575_THS73861_FILTER1_MASK
                                            |
                                            BOARD_PCF8575_THS73861_FILTER2_MASK)));
    regValue[0] = (UInt8) regValueTemp;

    switch (standard)
    {
        case FVID2_STD_1080P_60:
        case FVID2_STD_1080P_50:
        case FVID2_STD_SXGA_60:
        case FVID2_STD_SXGA_75:
        case FVID2_STD_SXGAP_60:
        case FVID2_STD_SXGAP_75:
        case FVID2_STD_UXGA_60:
            /* Filter2: 1, Filter1: 1 */
            regValueTemp = (UInt32) regValue[0] |
                           (BOARD_PCF8575_THS73861_FILTER1_MASK |
                            BOARD_PCF8575_THS73861_FILTER2_MASK);
            regValue[0] = (UInt8) regValueTemp;
            break;

        case FVID2_STD_1080I_60:
        case FVID2_STD_1080I_50:
        case FVID2_STD_1080P_24:
        case FVID2_STD_1080P_30:
        case FVID2_STD_720P_60:
        case FVID2_STD_720P_50:
        case FVID2_STD_SVGA_60:
        case FVID2_STD_SVGA_72:
        case FVID2_STD_SVGA_75:
        case FVID2_STD_SVGA_85:
        case FVID2_STD_XGA_60:
        case FVID2_STD_XGA_DSS_TDM_60:
        case FVID2_STD_XGA_70:
        case FVID2_STD_XGA_75:
        case FVID2_STD_XGA_85:
        case FVID2_STD_WXGA_60:
        case FVID2_STD_WXGA_75:
        case FVID2_STD_WXGA_85:
            /* Filter2: 0, Filter1: 1 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 ((UInt32) (~BOARD_PCF8575_THS73861_FILTER2_MASK)));
            regValue[0]  = (UInt8) regValueTemp;
            regValueTemp =
                ((UInt32) regValue[0] | (BOARD_PCF8575_THS73861_FILTER1_MASK));
            regValue[0] = (UInt8) regValueTemp;
            break;

        case FVID2_STD_480P:
        case FVID2_STD_576P:
        case FVID2_STD_VGA_60:
        case FVID2_STD_VGA_72:
        case FVID2_STD_VGA_75:
        case FVID2_STD_VGA_85:
            /* Filter2: 1, Filter1: 0 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 ((UInt32) (~BOARD_PCF8575_THS73861_FILTER1_MASK)));
            regValue[0]  = (UInt8) regValueTemp;
            regValueTemp =
                ((UInt32) regValue[0] | (BOARD_PCF8575_THS73861_FILTER2_MASK));
            regValue[0] = (UInt8) regValueTemp;
            break;

        case FVID2_STD_NTSC:
        case FVID2_STD_PAL:
        case FVID2_STD_480I:
        case FVID2_STD_576I:
        case FVID2_STD_D1:
            /* Filter2: 0, Filter1: 0 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 ((UInt32) ~(BOARD_PCF8575_THS73861_FILTER1_MASK |
                             BOARD_PCF8575_THS73861_FILTER2_MASK)));
            regValue[0] = (UInt8) regValueTemp;
            break;

        default:
            /* Filter2: 0, Filter1: 1 */
            regValueTemp =
                ((UInt32) regValue[0] &
                 (UInt32) (~BOARD_PCF8575_THS73861_FILTER2_MASK));
            regValue[0]  = (UInt8) regValueTemp;
            regValueTemp =
                ((UInt32) regValue[0] | (BOARD_PCF8575_THS73861_FILTER1_MASK));
            regValue[0] = (UInt8) regValueTemp;
            break;
    }

    retVal = Bsp_deviceRawWrite8(i2cInst, ioExpAddr, regValue, numRegs);
    GT_assert(BspBoardTrace, (retVal == FVID2_SOK));

    return (retVal);
}

static Int32 Bsp_boardLock(void)
{
    BspOsal_semWait(gBoardCommonObj.lock, BSP_OSAL_WAIT_FOREVER);

    return (BSP_SOK);
}

static Int32 Bsp_boardUnlock(void)
{
    BspOsal_semPost(gBoardCommonObj.lock);

    return (BSP_SOK);
}

