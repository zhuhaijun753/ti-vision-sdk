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
 * \file   stw_board.c
 *
 * \brief  This file contains the implementation of the APIs that abstract the
 *         board-specific details for StarterWare.
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
#include "uartStdio.h"
#include "hw_types.h"
#include "hw_l4per_cm_core.h"
#include "soc.h"
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "platforms/stw_platform.h"
#include "devices/stw_device.h"
#include "stw_boardPriv.h"
#ifndef TI814X_FAMILY_BUILD
#include "hw_ctrl_core.h"
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Enables the MMR region lock  */
/**<  Note : Only if required Enable the macro to lock the MMR region
 *    In the code if unlock MMR and lock MMR is not taken care properly ,
 *    by enabling this macro will result in hang while configuring pinmux ,
 *    PRCM etc.,
 */
/* #define BOARD_MMR_REG_LOCK_ENABLE*/

extern boardPinmuxBoardCfg_t gBoardTda2xxPinMuxData[
    NUM_OF_TDA2XXBOARD_PINMUX_CONFIGUARATIONS];
extern boardPinmuxBoardCfg_t gBoardTda3xxPinMuxData[
    NUM_OF_TDA3XXBOARD_PINMUX_CONFIGUARATIONS];

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct boardIdString_t
 *  \brief Structure to store board ID and string pair.
 */
typedef struct boardIdString
{
    boardId_t   boardId;
    /**< Board ID. */
    const char *pBoardIdStr;
    /**< Pointer to board ID string. */
} boardIdString_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Board module object. */
static boardCommonObj_t      gBoardCommonObj;

/** \brief Table containing all board ID strings */
static const boardIdString_t gBoardIdStrTable[] =
{
    {BOARD_UNKNOWN,       "UNKNOWN"       },
    {BOARD_VS,            "VS"            },
    {BOARD_VC,            "VC"            },
    {BOARD_VISION,        "Vision"        },
    {BOARD_VISION_TI81XX, "Vision(TI81XX)"},
    {BOARD_CATALOG,       "Catalog"       },
    {BOARD_CUSTOM,        "Custom"        },
    {BOARD_JAMR3,         "JAMR3"         },
    {BOARD_MULTIDES,      "MULTIDES"      },
    {BOARD_BASE_TDA2XX,   "TDA2XX BASE"   },
    {BOARD_BASE_TDA3XX,   "TDA3XX BASE"   },
    {BOARD_BASE_TI81XX,   "TI81XX BASE"   },
    {BOARD_BASE_TDA2EX,   "TDA2EX BASE"   },
};

static const char           *gBoardRevStr[] =
{
    "UNKNOWN",
    "REV A",
    "REV B",
    "REV C",
};

/** \brief Number of entries in board ID string table. */
#define BOARD_NUM_ID_STR_ENTRIES        (sizeof (gBoardIdStrTable) / \
                                         sizeof (boardIdString_t))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t BOARDInit(const boardInitParams_t *pInitPrms)
{
    int32_t           status = STW_SOK;
    boardInitParams_t localInitPrms;

    /* If NULL is passed the parameters will be initialized by default */
    if (NULL == pInitPrms)
    {
        pInitPrms = &localInitPrms;
        BoardInitParams_init(&localInitPrms);
    }
    memset(&gBoardCommonObj, 0, sizeof (gBoardCommonObj));

    gBoardCommonObj.boardId      = pInitPrms->boardId;
    gBoardCommonObj.baseBoardRev = pInitPrms->baseBoardRev;
    gBoardCommonObj.dcBoardRev   = pInitPrms->dcBoardRev;
    if (NULL != gBoardCommonObj.customData)
    {
        /* Below parameters can't be NULL */
        if ((gBoardCommonObj.customData->brdIdString == NULL) ||
            (gBoardCommonObj.customData->brdRevString == NULL) ||
            (gBoardCommonObj.customData->i2cData == NULL) ||
            (gBoardCommonObj.customData->brdData == NULL))
        {
            status = STW_EFAIL;
        }
    }

    /* Macro is used insted of checking for SoC. Any SoC API
     * cannot be called in board init as SoC init happens after board
     * init */
    if (status == STW_SOK)
    {
        if (NULL != gBoardCommonObj.customData)
        {
            if (NULL != gBoardCommonObj.customData->initFxn)
            {
                status = gBoardCommonObj.customData->initFxn();
            }
        }
        else
        {
            /* Use default built-in board functions */
#ifdef TDA2XX_FAMILY_BUILD
#ifdef TDA2EX_BUILD
            status = BOARDTda2exInit(pInitPrms);
#else
            status = BOARDTda2xxInit(pInitPrms);
#endif
#endif      /* ifdef TDA2XX_FAMILY_BUILD */

#ifdef TDA3XX_FAMILY_BUILD
            status = BOARDTda3xxInit(pInitPrms);
#endif      /* ifdef TDA3XX_FAMILY_BUILD */
        }
    }
    return (status);
}

int32_t BOARDDeInit(void *args)
{
    int32_t status = STW_SOK;

    return (status);
}

boardId_t BOARDGetId(void)
{
    if (BOARD_MAX == gBoardCommonObj.boardId)
    {
        if (PLATFORMGetId() != PLATFORM_ID_EVM)
        {
            gBoardCommonObj.boardId = BOARD_UNKNOWN;
        }
        else
        {
            if (PLATFORMIsTda2xxFamilyBuild())
            {
                if (PLATFORM_SOC_ID_TDA2EX == PLATFORMGetSocId())
                {
                    gBoardCommonObj.boardId = BOARDGetIdTda2ex();
                }
                else
                {
                    gBoardCommonObj.boardId = BOARDGetIdTda2xx();
                }
            }
            if (PLATFORMIsTda3xxFamilyBuild())
            {
                gBoardCommonObj.boardId = BOARDGetIdTda3xx();
            }
            if (PLATFORMIsTI814xFamilyBuild())
            {
                gBoardCommonObj.boardId = BOARDGetIdTI814x();
            }
        }
    }
    return (gBoardCommonObj.boardId);
}

const char *BOARDGetBoardName(void)
{
    const char *pBoardIdStr = NULL;
    uint32_t    entryCnt;
    boardId_t   boardId;

    if (NULL != gBoardCommonObj.customData)
    {
        pBoardIdStr = gBoardCommonObj.customData->brdIdString;
    }
    else
    {
        boardId = BOARDGetId();
        if (boardId > BOARD_MAX)
        {
            boardId = BOARD_UNKNOWN;
        }

        for (entryCnt = 0U; entryCnt < BOARD_NUM_ID_STR_ENTRIES; entryCnt++)
        {
            if (gBoardIdStrTable[entryCnt].boardId == boardId)
            {
                pBoardIdStr = gBoardIdStrTable[entryCnt].pBoardIdStr;
                break;
            }
        }
    }

    return (pBoardIdStr);
}

boardRev_t BOARDGetBaseBoardRev(void)
{
    if (BOARD_REV_MAX == gBoardCommonObj.baseBoardRev)
    {
        if (PLATFORMGetId() != PLATFORM_ID_EVM)
        {
            /*
             * Set to first permitted revision, since it is irrelevant for
             * non-EVM platforms.
             */
            gBoardCommonObj.baseBoardRev = BOARD_REV_A;
        }
        else
        {
            if (PLATFORMIsTda2xxFamilyBuild())
            {
                if (PLATFORM_SOC_ID_TDA2EX == PLATFORMGetSocId())
                {
                    gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTda2ex();
                }
                else
                {
                    gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTda2xx();
                }
            }
            if (PLATFORMIsTda3xxFamilyBuild())
            {
                gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTda3xx();
            }
            if (PLATFORMIsTI814xFamilyBuild())
            {
                gBoardCommonObj.baseBoardRev = BOARDGetBaseBoardRevTI814x();
            }
        }
    }
    return (gBoardCommonObj.baseBoardRev);
}

const char *BOARDGetBaseBoardRevName(void)
{
    boardRev_t  boardRev = BOARD_REV_UNKNOWN;
    const char *retPtr   = NULL;

    /* Check for out of bound access */
    if (BOARD_REV_MAX == ((sizeof (gBoardRevStr)) / (sizeof (char *))))
    {
        boardRev = BOARDGetBaseBoardRev();
        if (boardRev >= BOARD_REV_MAX)
        {
            boardRev = BOARD_REV_UNKNOWN;
        }
        retPtr = gBoardRevStr[boardRev];
    }

    return (retPtr);
}

boardRev_t BOARDGetDcRev(void)
{
    if (BOARD_REV_MAX == gBoardCommonObj.dcBoardRev)
    {
        if (PLATFORMGetId() != PLATFORM_ID_EVM)
        {
            /*
             * Set to first permitted revision, since it is irrelevant for
             * non-EVM platforms.
             */
            gBoardCommonObj.dcBoardRev = BOARD_REV_A;
        }
        else
        {
            if (PLATFORMIsTda2xxFamilyBuild())
            {
                if (PLATFORM_SOC_ID_TDA2EX == PLATFORMGetSocId())
                {
                    gBoardCommonObj.dcBoardRev = BOARDGetDcRevTda2ex();
                }
                else
                {
                    gBoardCommonObj.dcBoardRev = BOARDGetDcRevTda2xx();
                }
            }
            if (PLATFORMIsTda3xxFamilyBuild())
            {
                gBoardCommonObj.dcBoardRev = BOARDGetDcRevTda3xx();
            }
            if (PLATFORMIsTI814xFamilyBuild())
            {
                gBoardCommonObj.dcBoardRev = BOARDGetDcRevTI814x();
            }
        }
    }
    return (gBoardCommonObj.dcBoardRev);
}

const char *BOARDGetDcRevName(void)
{
    boardRev_t  boardRev = BOARD_REV_UNKNOWN;
    const char *retPtr   = NULL;

    /* Check for out of bound access */
    if (BOARD_REV_MAX == ((sizeof (gBoardRevStr)) / (sizeof (char *))))
    {
        boardRev = BOARDGetDcRev();
        if (boardRev >= BOARD_REV_MAX)
        {
            boardRev = BOARD_REV_UNKNOWN;
        }
        retPtr = gBoardRevStr[boardRev];
    }

    return (retPtr);
}

const boardI2cData_t *BOARDGetI2cData(void)
{
    const boardI2cData_t *i2cData = NULL;

    if (PLATFORMIsTda2xxFamilyBuild())
    {
        if (PLATFORM_SOC_ID_TDA2EX == PLATFORMGetSocId())
        {
            i2cData = BOARDGetI2cDataTda2ex();
        }
        else
        {
            i2cData = BOARDGetI2cDataTda2xx();
        }
    }
    if (PLATFORMIsTda3xxFamilyBuild())
    {
        i2cData = BOARDGetI2cDataTda3xx();
    }
    if (PLATFORMIsTI814xFamilyBuild())
    {
        i2cData = BOARDGetI2cDataTI814x();
    }

    return (i2cData);
}

const boardData_t *BOARDGetData(void)
{
    const boardData_t *pBoardData = NULL;

    if (NULL != gBoardCommonObj.customData)
    {
        pBoardData = gBoardCommonObj.customData->brdData;
    }
    else
    {
        if (PLATFORMIsTda2xxFamilyBuild())
        {
            if (PLATFORM_SOC_ID_TDA2EX == PLATFORMGetSocId())
            {
                pBoardData = BOARDGetDataTda2ex();
            }
            else
            {
                pBoardData = BOARDGetDataTda2xx();
            }
        }
        if (PLATFORMIsTda3xxFamilyBuild())
        {
            pBoardData = BOARDGetDataTda3xx();
        }
        if (PLATFORMIsTI814xFamilyBuild())
        {
            pBoardData = BOARDGetDataTI814x();
        }
    }
    return (pBoardData);
}

uint32_t BOARDGetDeviceCtrlModId(uint32_t devId, uint32_t devInstNum)
{
    uint32_t ctrlModId = INVALID_ID;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    ctrlModId = pDevData->ctrlModId;
                    break;
                }
            }
        }

        if (INVALID_ID == ctrlModId)
        {
            console_print_string("\nInvalid device ID!!");
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (ctrlModId);
}

uint32_t BOARDGetDeviceCtrlModInstNum(uint32_t devId, uint32_t devInstNum)
{
    uint32_t ctrlModInstNum = INVALID_INST_NUM;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    ctrlModInstNum = pDevData->ctrlModInstNum;
                    break;
                }
            }
        }
        if (INVALID_INST_NUM == ctrlModInstNum)
        {
            console_print_string("\nInvalid device ID!!");
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (ctrlModInstNum);
}

uint32_t BOARDGetDeviceCtrlInfo(uint32_t devId, uint32_t devInstNum)
{
    uint32_t ctrlInfo = INVALID_INFO;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    ctrlInfo = pDevData->ctrlInfo;
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (ctrlInfo);
}

uint32_t BOARDGetDeviceDataModId(uint32_t devId, uint32_t devInstNum)
{
    uint32_t dataModId = INVALID_ID;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    dataModId = pDevData->dataModId;
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (dataModId);
}

uint32_t BOARDGetDeviceDataModInstNum(uint32_t devId, uint32_t devInstNum)
{
    uint32_t dataModInstNum = INVALID_INST_NUM;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum))
                {
                    dataModInstNum = pDevData->dataModInstNum;
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (dataModInstNum);
}

int32_t BOARDPowerOnDevice(uint32_t devId,
                           uint32_t devInstNum,
                           uint32_t powerOn)
{
    int32_t  status = STW_SOK;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum) &&
                    (pDevData->pFnPowerOnDev != NULL))
                {
                    status = pDevData->pFnPowerOnDev(devId, devInstNum, powerOn);
                    if (STW_SOK != status)
                    {
                        console_print_string("\nDevice power-on failed!!");
                    }
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (status);
}

int32_t BOARDSelectDevice(uint32_t devId, uint32_t devInstNum)
{
    int32_t  status = STW_SOK;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum) &&
                    (pDevData->pFnSelectDev != NULL))
                {
                    status = pDevData->pFnSelectDev(devId, devInstNum);
                    if (STW_SOK != status)
                    {
                        console_print_string("\nDevice select failed!!");
                    }
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (status);
}

int32_t BOARDResetDevice(uint32_t devId, uint32_t devInstNum)
{
    int32_t  status = STW_SOK;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devId) &&
                    (pDevData->devInstNum == devInstNum) &&
                    (pDevData->pFnResetDev != NULL))
                {
                    status = pDevData->pFnResetDev(devId, devInstNum);
                    if (STW_SOK != status)
                    {
                        console_print_string("\nDevice reset failed!!");
                    }
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (status);
}

int32_t BOARDSelectMode(uint32_t    devId,
                        uint32_t    instId,
                        boardMode_t boardMod)
{
    int32_t retVal = STW_SOK;

    if (NULL != gBoardCommonObj.customData)
    {
        if (NULL != gBoardCommonObj.customData->selectModeFxn)
        {
            retVal = gBoardCommonObj.customData->selectModeFxn(devId,
                                                               instId,
                                                               boardMod);
        }
    }
    else
    {
        if (PLATFORMIsTda3xxFamilyBuild())
        {
            retVal = BOARDSelectModeTda3xx(devId, instId, boardMod);
        }
    }
    return (retVal);
}

void BOARDPrintInfo(void)
{
    const char *baseBoardrevision = NULL;
    const char *boardIdStr        = NULL;
    const char *boardRevStr       = NULL;

    boardIdStr = BOARDGetBoardName();
    if (boardIdStr != NULL)
    {
        console_print_string(" \r\nBoard Detected               : ");
        console_print_string(boardIdStr);
    }
    else
    {
        console_print_string(" \r\nNULL Pointer Detected boardIdStr  : ");
    }

    baseBoardrevision = BOARDGetBaseBoardRevName();
    if (baseBoardrevision != NULL)
    {
        console_print_string(" \r\nBase Board Revision          : ");
        console_print_string(baseBoardrevision);
    }
    else
    {
        console_print_string(
            " \r\n baseBoardrevision out of bound error : ");
    }

    boardRevStr = BOARDGetDcRevName();
    if (boardRevStr != NULL)
    {
        console_print_string(" \r\nDaughter Card Revision       : ");
        console_print_string(boardRevStr);
    }
    else
    {
        console_print_string(
            " \r\n Daughter Card Revision out of bound error  : ");
    }
}

void BOARDConfigModulePinMux(uint32_t moduleId,
                             uint32_t instNum,
                             uint32_t boardMod)
{
    const boardPinmuxBoardCfg_t *pPinmuxData = NULL;
    uint32_t i = 0;
    const boardData_t           *pBoardData = NULL;

    /* Get board Data */
    if (NULL == pBoardData)
    {
        pBoardData = BOARDGetData();
    }

    /* Get module Data */
    if (NULL != pBoardData)
    {
        pPinmuxData = pBoardData->pPinmuxData;
        if (pPinmuxData != NULL)
        {
            for (i = 0; (DEVICE_ID_INVALID != pPinmuxData[i].moduleId); i++)
            {
                if ((pPinmuxData[i].moduleId == moduleId) &&
                    (pPinmuxData[i].instNum == instNum) &&
                    ((pPinmuxData[i].boardMode & boardMod) == boardMod))
                {
                    PLATFORMSetPinmuxRegs(pPinmuxData[i].regOffset,
                                          pPinmuxData[i].regVal);
                }
            }
        }
        else
        {
            console_print_string(" \r\nNULL Pointer Detected pPinmuxData  : ");
        }
    }
    return;
}

uint32_t BOARDIsDevicePresent(uint32_t devId)
{
    uint32_t found = FALSE;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if (pDevData->devId == devId)
                {
                    /* Found at least one instance of the specified device. */
                    found = (uint32_t) TRUE;
                    break;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (found);
}

uint32_t BOARDGetNumDevices(uint32_t devId)
{
    uint32_t                 numDevFound = 0U;
    uint32_t                 devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if (pDevData->devId == devId)
                {
                    numDevFound++;
                }
            }
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (numDevFound);
}

uint32_t BOARDGetVideoDeviceInstId(uint32_t devDrvId,
                                   uint32_t drvId,
                                   uint32_t drvInstId)
{
    uint32_t instId = BOARD_INVALID_INST_ID;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devDrvId) &&
                    (pDevData->dataModId == drvId) &&
                    (pDevData->dataModInstNum == drvInstId))
                {
                    instId = pDevData->devInstNum;
                    break;
                }
            }
        }
        if (BOARD_INVALID_INST_ID == instId)
        {
            console_print_string("\nInvalid device driver ID!!");
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (instId);
}

uint32_t BOARDGetVideoDeviceI2cInstId(uint32_t devDrvId,
                                      uint32_t drvId,
                                      uint32_t drvInstId)
{
    uint32_t i2cInstId = HSI2C_INST_MAX;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devDrvId) &&
                    (pDevData->dataModId == drvId) &&
                    (pDevData->dataModInstNum == drvInstId))
                {
                    i2cInstId = pDevData->ctrlModInstNum;
                    break;
                }
            }
        }

        if (HSI2C_INST_MAX == i2cInstId)
        {
            console_print_string("\nInvalid device driver ID!!");
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (i2cInstId);
}

uint32_t BOARDGetVideoDeviceI2cAddr(uint32_t devDrvId,
                                    uint32_t drvId,
                                    uint32_t drvInstId)
{
    uint32_t i2cAddr = 0U;
    uint32_t devCnt;
    const boardData_t       *pBoardData;
    const boardDeviceData_t *pDevData;

    pBoardData = BOARDGetData();
    if (pBoardData != NULL)
    {
        for (devCnt = 0U; devCnt < pBoardData->numDev; devCnt++)
        {
            if (pBoardData->pDevData == NULL)
            {
                console_print_string(
                    " \r\nNULL Pointer Detected pBoardData->pDevData : ");
            }
            else
            {
                pDevData = &pBoardData->pDevData[devCnt];
                if ((pDevData->devId == devDrvId) &&
                    (pDevData->dataModId == drvId) &&
                    (pDevData->dataModInstNum == drvInstId))
                {
                    i2cAddr = pDevData->ctrlInfo;
                    break;
                }
            }
        }
        if (0U == i2cAddr)
        {
            console_print_string("\nInvalid device driver ID!!");
        }
    }
    else
    {
        console_print_string(
            " \r\nNULL Pointer Detected pBoardData : ");
    }
    return (i2cAddr);
}

/**
 *  \brief Returns the console Instance ID of the connected Board
 *
 *
 *  \return console Instance ID
 */
uint32_t BOARDGetConsoleInstID(void)
{
    uint32_t uartInstId = DEVICE_UART_INST_ID_1;

#if (defined (TDA2XX_FAMILY_BUILD))
    uartInstId = DEVICE_UART_INST_ID_1;
#elif (defined (TDA3XX_FAMILY_BUILD))
    uartInstId = DEVICE_UART_INST_ID_3;
#else
    /* Nothing to be done here */
#endif
    return uartInstId;
}

/**
 * \brief   Configures IO pins needed by UART console. This API uses the pin mux
 *          data and configures the pinmux of UART console for default mode
 *
 * \param   uartInstId     Instance number of the UART console
 *
 **/
void BOARDConfigConsolePinMux(uint32_t uartInstId)
{
#if (defined (TDA2XX_FAMILY_BUILD))
#if (defined (TDA2XX_BUILD))
    BOARDTda2xxConfigConsolePinMux(uartInstId);
#elif (defined (TDA2EX_BUILD))
    BOARDTda2exConfigConsolePinMux(uartInstId);
#endif
#elif (defined (TDA3XX_FAMILY_BUILD))
    BOARDTda3xxConfigConsolePinMux(uartInstId);
#else
    /* Nothing to be done here */
#endif

    return;
}

