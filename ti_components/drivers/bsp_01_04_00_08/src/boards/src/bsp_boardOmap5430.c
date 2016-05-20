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
 *  \file bsp_boardOmap5430.c
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
#include <boards/bsp_board.h>
#include <bsp_boardPriv.h>
#include <devices/bsp_device.h>
#include <boards/bsp_board.h>
#include <vps/vps.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_BoardI2cInstData gBoardOmap5430I2cInstData[] =
{
    {
        0,                                  /* instId */
        0,                                  /* baseAddr */
        0,                                  /* intNum */
        0                                   /* busClkKHz */
    }
};

static Bsp_BoardI2cData     gBoardOmap5430I2cData =
{
    0,                                      /* numI2c */
    gBoardOmap5430I2cInstData,              /* i2cData */
    0,                                      /* probeInstId */
};

/* Omap5430 Custom board data */
static Bsp_BoardData        gBoardOmap5430CustomData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

/* Omap5430 Default board data */
static Bsp_BoardData        gBoardOmap5430DefaultData =
{
    0U,                                     /* numDev */
    NULL,                                   /* devData */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Bsp_BoardId Bsp_boardGetIdOmap5430(void)
{
    Bsp_BoardId    boardId = BSP_BOARD_UNKNOWN;
    Bsp_PlatformId platformId;

    platformId = Bsp_platformGetId();
    if ((BSP_PLATFORM_ID_ZEBU == platformId) ||
        (BSP_PLATFORM_ID_VIRTIO == platformId))
    {
        boardId = BSP_BOARD_VC;
    }
    else
    {
        /* Board ID not yet detected, find and save it */
        boardId = BSP_BOARD_VC;
    }

    return (boardId);
}

Bsp_BoardRev Bsp_boardGetBaseBoardRevOmap5430(void)
{
    /* Only one revision of board till date */
    return (BSP_BOARD_REV_A);
}

Bsp_BoardRev Bsp_boardGetDcRevOmap5430(void)
{
    /* Only one revision of board till date */
    return (BSP_BOARD_REV_A);
}

const Bsp_BoardI2cData *Bsp_boardGetI2cDataOmap5430(void)
{
    return (&gBoardOmap5430I2cData);
}

const Bsp_BoardData *Bsp_boardGetDataOmap5430(void)
{
    Bsp_BoardId          boardId;
    const Bsp_BoardData *boardData = NULL;

    boardId = Bsp_boardGetId();
    switch (boardId)
    {
        case BSP_BOARD_CUSTOM:
            boardData = &gBoardOmap5430CustomData;
            break;

        case BSP_BOARD_UNKNOWN:
        default:
            boardData = &gBoardOmap5430DefaultData;
            break;
    }

    return (boardData);
}

