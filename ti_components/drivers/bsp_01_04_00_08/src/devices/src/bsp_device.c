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
 *  \file bsp_device.c
 *
 *  \brief File containing the BSP devices functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <bsp_devicePriv.h>
#include <tvp5158/bspdrv_tvp5158.h>
#include <tvp7002/bspdrv_tvp7002.h>
#include <sii9127/bspdrv_sii9127.h>
#include <mt9v022/bspdrv_mt9v022.h>
#include <ov1063x/bspdrv_ov1063x.h>
#include <ar0132/bspdrv_ar0132.h>
#include <ar0140/bspdrv_ar0140.h>
#include <ar0132rccc/bspdrv_ar0132rccc.h>
#include <lcdCtrl/bspdrv_lcdCtrl.h>
#include <sii9022a/bspdrv_sii9022a.h>
#include <ds90uh925/bspdrv_ds90uh925.h>
#include <ds90uh926/bspdrv_ds90uh926.h>
#include <ioexp/bspdrv_ioexp.h>
#include <adv7611/bspdrv_adv7611.h>
#include <ov10640/bspdrv_ov10640.h>
#include <imx224/bspdrv_imx224.h>

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

static Bsp_DeviceInitParams gDevInitPrm;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief BSP Devices init function.
 */
Int32 Bsp_deviceInit(const Bsp_DeviceInitParams *pPrm)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    const Bsp_BoardI2cData *i2cData;
    Bsp_BoardI2cInstData   *i2cInstData;

    /* Init global */
    BspDeviceInitParams_init(&gDevInitPrm);
    gDevInitPrm.isI2cInitReq = FALSE;

    if(NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device Init: NULL init pointer\n");
        retVal = BSP_EBADARGS;
    }

    if((BSP_SOK == retVal) && (TRUE == pPrm->isI2cInitReq))
    {
        retVal = Bsp_deviceI2cInit();
        if(BSP_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device Init: I2C init failed\n");
        }
        else
        {
            gDevInitPrm.isI2cInitReq = pPrm->isI2cInitReq;

            if(TRUE == pPrm->isI2cProbingReq)
            {
                i2cData = Bsp_boardGetI2cData();
                GT_assert(BspDeviceTrace, (NULL != i2cData));
                GT_assert(BspDeviceTrace, (NULL != i2cData->instData));
                for(instCnt = 0U; instCnt < i2cData->numInst; instCnt++)
                {
                    i2cInstData = &i2cData->instData[instCnt];
                    Bsp_deviceI2cProbeAll(i2cInstData->instId);
                }
            }

            retVal += Bsp_tvp5158Init();
            retVal += Bsp_tvp7002Init();
            retVal += Bsp_sii9127Init();
            retVal += Bsp_mt9v022Init();
            retVal += Bsp_ov1063xInit();
            retVal += Bsp_ar0132Init();
            retVal += Bsp_ar0140Init();
            retVal += Bsp_ar0132rcccInit();
            retVal += Bsp_lcdCtrlInit();
            retVal += Bsp_sii9022aInit();
            retVal += Bsp_ds90uh925Init();
            retVal += Bsp_ds90uh926Init();
            retVal += Bsp_ioexpInit();
            retVal += Bsp_adv7611Init();
            retVal += Bsp_ov10640Init();
            retVal += Bsp_imx224Init();
        }
    }

    return (retVal);
}

/**
 *  \brief BSP Devices deinit function.
 */
Int32 Bsp_deviceDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

    if(TRUE == gDevInitPrm.isI2cInitReq)
    {
        retVal += Bsp_imx224DeInit();
        retVal += Bsp_ov10640DeInit();
        retVal += Bsp_adv7611DeInit();
        retVal += Bsp_ioexpDeInit();
        retVal += Bsp_ds90uh926DeInit();
        retVal += Bsp_ds90uh925DeInit();
        retVal += Bsp_sii9022aDeInit();
        retVal += Bsp_lcdCtrlDeInit();
        retVal += Bsp_ar0132rcccDeInit();
        retVal += Bsp_ar0140DeInit();
        retVal += Bsp_ar0132DeInit();
        retVal += Bsp_ov1063xDeInit();
        retVal += Bsp_mt9v022DeInit();
        retVal += Bsp_sii9127DeInit();
        retVal += Bsp_tvp7002DeInit();
        retVal += Bsp_tvp5158DeInit();
        retVal += Bsp_deviceI2cDeInit();
    }

    return (retVal);
}

