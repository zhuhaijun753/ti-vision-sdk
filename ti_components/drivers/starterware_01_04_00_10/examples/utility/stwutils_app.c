/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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
 *  \file stwutils_app.c
 *
 *  \brief This file implements application level generic helper functions.
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
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "stw_boardPriv.h"
#include "platforms/stw_platform.h"
#include "devices/stw_device.h"
#include "stwutils_app.h"
#ifndef TI814X_FAMILY_BUILD
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  None
 */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure to store app objects.
 */
typedef struct stwUtils_AppObj
{
    Bool             initDone;
    /**< Initialization done flag. */
    platformId_t     platfrmId;
    /**< Platform identifier. */
    platformCpuRev_t cpuRev;
    /**< CPU version identifier. */
} stwUtils_AppObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  None
 */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief STW Utils app object used for storing semaphore handle, flags etc. */
static stwUtils_AppObj_t gStwUtilsAppObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  StwUtils_appInit
 *  \brief STW application utils init function.
 */
int32_t StwUtils_appInit(void)
{
    int32_t retVal = STW_SOK;
    stwUtils_AppObj_t *appObj = &gStwUtilsAppObj;

    memset(appObj, (int32_t) 0, sizeof (*appObj));

    /* Get platform type, board and CPU revisions */
    appObj->platfrmId = PLATFORMGetId();
    if ((appObj->platfrmId == PLATFORM_ID_UNKNOWN) ||
        (appObj->platfrmId >= PLATFORM_ID_MAX))
    {
        console_print_string("\nError: Unrecognized platform!!");
        retVal = STW_EFAIL;
    }
    appObj->cpuRev = PLATFORMGetCpuRev();
    if (appObj->cpuRev >= PLATFORM_CPU_REV_MAX)
    {
        console_print_string("\nError: Unrecognized CPU version!!");
        retVal = STW_EFAIL;
    }

    if (STW_SOK == retVal)
    {
        appObj->initDone = (Bool) TRUE;
    }

    return (retVal);
}

/**
 *  StwUtils_appDeInit
 *  \brief STW application utils deinit function.
 */
int32_t StwUtils_appDeInit(void)
{
    int32_t retVal = STW_SOK;
    stwUtils_AppObj_t *appObj = &gStwUtilsAppObj;

    appObj->initDone = (Bool) FALSE;

    return (retVal);
}

/**
 *  StwUtils_appDefaultInit
 *  \brief STW application utils function to call all the default init
 *  functions.
 */
int32_t StwUtils_appDefaultInit(stwAppInitParams_t stwAppInitPrms)
{
    int32_t              retVal = STW_SOK;
    boardInitParams_t    boardInitPrms;
    deviceInitParams_t   deviceInitPrms;
    platformInitParams_t platInitPrms;

    BoardInitParams_init(&boardInitPrms);
    /* Override board detection if I2C is disabled */
    if (((Bool) TRUE) != ((Bool) stwAppInitPrms.isI2cInitReq))
    {
        boardInitPrms.boardId      = BOARD_UNKNOWN;
        boardInitPrms.baseBoardRev = BOARD_REV_UNKNOWN;
        boardInitPrms.dcBoardRev   = BOARD_REV_UNKNOWN;
    }

    retVal = BOARDInit(&boardInitPrms);
    if (STW_SOK == retVal)
    {
        PLATFORMInitParams_init(&platInitPrms);
        retVal = PLATFORMInit(&platInitPrms);
        if (STW_SOK != retVal)
        {
            console_print_string("\nError: Platform Init failed!!");
        }
    }
    else
    {
        console_print_string("\nError: BOARDInit Init failed!!");
    }

    if (STW_SOK == retVal)
    {
        retVal = StwUtils_appUartModuleInit(stwAppInitPrms.isUartInitReq);
        if (STW_SOK != retVal)
        {
            console_print_string(
                "\nError: StwUtils_appUartModuleInit Init failed!!");
        }
    }

    if (STW_SOK == retVal)
    {
        /* Override I2C init for non-EVM builds */
        if (PLATFORM_ID_EVM != PLATFORMGetId())
        {
            stwAppInitPrms.isI2cInitReq = (uint32_t) FALSE;
        }
        if (stwAppInitPrms.isI2cInitReq)
        {
            DEVICEInitParams_init(&deviceInitPrms);

            deviceInitPrms.isI2cProbingReq = (uint32_t) FALSE;

            retVal += DEVICEInit(&deviceInitPrms);
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                console_print_string("\nError: Device Init failed!!");
            }
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        retVal += StwUtils_appInit();
        if (STW_SOK != retVal)
        {
            console_print_string("\nError: App Utils Init failed!!");
        }
    }
    StwUtils_appPrintInfo();
    return (retVal);
}

void StwUtils_appPrintInfo(void)
{
    /* Print platform info*/
    console_print_string("\n \r");
    PLATFORMPrintInfo();
    BOARDPrintInfo();
    console_print_string("\n \r");
}

/**
 *  StwUtils_appDefaultDeInit
 *  \brief STW application utils function to call all the default de-init
 *  functions.
 */
int32_t StwUtils_appDefaultDeInit(stwAppDeInitParams_t stwAppDeInitPrms)
{
    int32_t retVal = STW_SOK;

    retVal = StwUtils_appDeInit();
    if (STW_SOK != retVal)
    {
        console_print_string("\nError: App Utils De-Init failed!!");
    }
    /* Override I2C de-init for non-EVM builds */
    if (PLATFORM_ID_EVM != PLATFORMGetId())
    {
        stwAppDeInitPrms.isI2cDeInitReq = (uint32_t) FALSE;
    }

    if (((Bool) TRUE) == ((Bool) stwAppDeInitPrms.isI2cDeInitReq))
    {
        retVal = DEVICEDeInit(NULL);
        if (STW_SOK != retVal)
        {
            console_print_string("\nError: Device De-Init failed!!");
        }
    }

    retVal = PLATFORMDeInit(NULL);
    if (STW_SOK != retVal)
    {
        console_print_string("\nError: STW Platform De-Init failed!!");
    }

    retVal = BOARDDeInit(NULL);
    if (STW_SOK != retVal)
    {
        console_print_string("\nError: STW Board De-Init failed!!");
    }

    return (retVal);
}

int32_t StwUtils_appUartModuleInit(uint32_t uartInitReq)
{
    int32_t  retVal = STW_SOK;
#ifndef TI814X_FAMILY_BUILD
    uint32_t uartInstId;
    pmhalPrcmModuleId_t pmModInstId;

    if (uartInitReq)
    {
        uartInstId = BOARDGetConsoleInstID();
        if (uartInstId == DEVICE_UART_INST_ID_3)
        {
            pmModInstId = PMHAL_PRCM_MOD_UART3;
        }
        else if (uartInstId == DEVICE_UART_INST_ID_1)
        {
            pmModInstId = PMHAL_PRCM_MOD_UART1;
        }
        else
        {
            retVal = STW_EFAIL;
        }

        if (retVal == STW_SOK)
        {
            /*Enable the module - uart*/
            retVal = PMHALModuleModeSet(pmModInstId,
                                        PMHAL_PRCM_MODULE_MODE_ENABLED,
                                        PM_TIMEOUT_INFINITE);
            if (retVal != PM_SUCCESS)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                UARTStdioInit();
            }
        }
    }
#endif
    return retVal;
}

