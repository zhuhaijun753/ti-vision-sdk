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
 *  \file stw_device.c
 *
 *  \brief File containing the STW device functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include <devices/stw_device.h>
#include <devices/stw_deviceIoexp.h>
#include "ioexp/stw_deviceIoexpPriv.h"
#include "stw_deviceI2cPriv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static deviceInitParams_t gDevInitPrm;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  \brief STW Devices init function.
 */
int32_t DEVICEInit(const deviceInitParams_t *pPrm)
{
    int32_t  retVal = STW_SOK;
    uint32_t instCnt;
    const boardI2cData_t *i2cData;
    boardI2cInstData_t   *i2cInstData;

    /* Init global */
    DEVICEInitParams_init(&gDevInitPrm);
    gDevInitPrm.isI2cInitReq = (uint32_t) FALSE;

    if (NULL == pPrm)
    {
        console_print_string("\nDevice Init: NULL init pointer");
        retVal = STW_EFAIL;
    }

    if ((STW_SOK == retVal) && (TRUE == pPrm->isI2cInitReq))
    {
        retVal = DEVICEI2cInit(pPrm);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            console_print_string("\nDevice Init: I2C init failed");
        }
        else
        {
            gDevInitPrm.isI2cInitReq = pPrm->isI2cInitReq;

            if (TRUE == pPrm->isI2cProbingReq)
            {
                i2cData = BOARDGetI2cData();
                if ((NULL != i2cData) && (NULL != i2cData->pInstData))
                {
                    for (instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
                    {
                        i2cInstData = &i2cData->pInstData[instCnt];
                        DEVICEI2cProbeAll(i2cInstData->instId);
                    }
                }
                else
                {
                    console_print_string("\nDevice Init: NULL i2cData pointer");
                    retVal = STW_EFAIL;
                }
            }
        }
        retVal = DEVICEIoexpInit();
    }
    return (retVal);
}

/**
 *  \brief STW Devices deinit function.
 */
int32_t DEVICEDeInit(void *args)
{
    int32_t retVal = STW_SOK;

    if (TRUE == gDevInitPrm.isI2cInitReq)
    {
        retVal += DEVICEIoexpDeInit();
        retVal += DEVICEI2cDeInit();
    }

    return (retVal);
}

