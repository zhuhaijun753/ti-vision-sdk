/******************************************************************************
 *                                                                            *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file bsputils_ub960.c
 *
 *  \brief Implements APIs to initialize, de-initialize UB960 EVM, address
 *          aliases & reset sensors.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <common/bsp_common.h>
#include <boards/bsp_board.h>
#include <i2c/bsp_i2c.h>
#include <devices/bsp_device.h>
#include <bsputils_app.h>
#include <bsputils_ub960.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */


/**
 *  \brief Register address and value pair, with delay.
 */
typedef struct
{
    UInt8 nRegAddr;
    /**< Register Address */
    UInt8 nRegValue;
    /**< Slave Address */
    UInt32 nDelay;
    /**< Delay to be applied, after the register is programmed */
} BspUtils_Ub960I2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */


BspUtils_Ub960I2cParams gUb960Cfg[] = {

    {0x1F, 0x05, 0x4FF},

    /* TIDA00262 1 */
    {0x4C, 0x01, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, (TIDA00262_PORT_0_SER_ADDR << 1U), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, (TIDA00262_PORT_0_SENSOR_ADDR << 1U), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0x2B, 0x0},
    {0x71, 0x2C, 0x0},

    /* TIDA00262 2 */
    {0x4C, 0x12, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, (TIDA00262_PORT_1_SER_ADDR << 1U), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, (TIDA00262_PORT_1_SENSOR_ADDR << 1U), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0x6B, 0x0},
    {0x71, 0x6C, 0x0},

    /* TIDA00262 3 */
    {0x4C, 0x24, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, (TIDA00262_PORT_2_SER_ADDR << 1U), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, (TIDA00262_PORT_2_SENSOR_ADDR << 1U), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0xAB, 0x0},
    {0x71, 0xAC, 0x0},

    /* TIDA00262 4 */
    {0x4C, 0x38, 0x0},
    {0x58, 0x58, 0x0},
    {0x5D, 0xB0, 0x0},
    {0x65, (TIDA00262_PORT_3_SER_ADDR << 1U), 0x0},
    {0x5E, 0x20, 0x0},
    {0x66, (TIDA00262_PORT_3_SENSOR_ADDR << 1U), 0x0},
    {0x7C, 0x00, 0x0},
    {0x6e, 0x99, 0x0},
    {0x70, 0xEB, 0x0},
    {0x71, 0xEC, 0x0},

    {0xB0, 0x1C, 0xFFF},
    {0xB1, 0x13, 0xFFF},
    {0xB2, 0x1F, 0xFFF},

    {0x32, 0x01, 0x0},
    {0x33, 0x03, 0x0},
    {0x20, 0x00, 0x0}
};

BspUtils_Ub960I2cParams gUb960ResetCfg[] = {
    {0x01, 0x2, 0x0}
};

BspUtils_Ub960I2cParams gTida00262SerCfg[] = {
    {0x03, 0xC5, 0x0},
    {0x0D, 0x99, 0x0},

    /* Changing the default I2C clock rate to 100 KHz */
    /* Default  0x82 = 74 kbits/sec
                0x64 = 100 kbps
                0x32 = 400 kbps */
    {0x11, 0x32, 0x0},  /* SCL High period */
    {0x12, 0x32, 0x0}   /* SCL Low period */
};

BspUtils_Ub960I2cParams gTida00262ResetCfg[] = {
    {0x0D, 0x11, 0x0}
};

BspUtils_Ub960SourceI2cAddr gSlaveAliases;

/* ========================================================================== */
/*                          Function Implementation                           */
/* ========================================================================== */

Int32 BspUtils_appInitUb960(UInt32 instId,
                            const BspUtils_Ub960SourceI2cAddr *pSlaveAddr,
                            BspUtils_Ub960Status *pStatus)
{
    Int32   retVal = BSP_EBADARGS;
    UInt32  nIdx;
    UInt32  i2cInst, serAddr, sensorAddr;
    volatile UInt32 count;

    if ((NULL != pStatus) && (NULL != pSlaveAddr))
    {
        retVal = BSP_SOK;
        gSlaveAliases.slaveAddr = pSlaveAddr->slaveAddr;
        gSlaveAliases.numSource = pSlaveAddr->numSource;
    }

    if (BSP_SOK == retVal)
    {
        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
            gSlaveAliases.rSlave1Addr[nIdx] = pSlaveAddr->rSlave1Addr[nIdx];
            gSlaveAliases.rSlave2Addr[nIdx] = pSlaveAddr->rSlave2Addr[nIdx];
        }

        count = 0U;
        for (nIdx = 0U;
             (nIdx < (sizeof (gUb960Cfg) / sizeof (gUb960Cfg[0U])));
             nIdx++)
        {
            if (0x65 == gUb960Cfg[nIdx].nRegAddr)
            {
                gUb960Cfg[nIdx].nRegValue =
                        (gSlaveAliases.rSlave1Addr[count] << 1U);
            }
            if (0x66 == gUb960Cfg[nIdx].nRegAddr)
            {
                gUb960Cfg[nIdx].nRegValue =
                        (gSlaveAliases.rSlave2Addr[count] << 1U);
                count++;
            }
            GT_assert(BspAppTrace, (BSPUTILS_UB960EVM_MAX_PORTS >= count));
        }

        for (nIdx = 0U;
             (nIdx < (sizeof (gUb960Cfg) / sizeof (gUb960Cfg[0U])));
             nIdx++)
        {
            retVal = Bsp_deviceWrite8(
                UB960_ACCESSIBLE_FROM_I2C_INST,
                gSlaveAliases.slaveAddr,
                &(gUb960Cfg[nIdx].nRegAddr),
                &(gUb960Cfg[nIdx].nRegValue),
                (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_0trace(BspAppTrace, GT_ERR,
                          "Could not configure UB960 !!!\n");
                break;
            }

            if (0 != gUb960Cfg[nIdx].nDelay)
            {
                count = gUb960Cfg[nIdx].nDelay;
                while (count)
                {
                    count--;
                }
            }
        }
    }

    /* Figure out which modules are connected */
    if (BSP_SOK == retVal)
    {
        pStatus->numDetected = 0U;
        i2cInst = UB960_ACCESSIBLE_FROM_I2C_INST;
        for (nIdx = 0U; nIdx < BSPUTILS_UB960EVM_MAX_PORTS; nIdx++)
        {
            serAddr = gSlaveAliases.rSlave1Addr[nIdx];
            sensorAddr = gSlaveAliases.rSlave2Addr[nIdx];
            retVal = Bsp_deviceI2cProbeDevice(i2cInst, (UInt8)serAddr);
            retVal += Bsp_deviceI2cProbeDevice(i2cInst, (UInt8)sensorAddr);
            if (BSP_SOK == retVal)
            {
                pStatus->portNum[nIdx] = nIdx;
                pStatus->numDetected++;
            }
            else
            {
                pStatus->portNum[nIdx] =
                                BSPUTILS_UB960EVM_NO_SOURCE_DETECTED;
            }
        }
        retVal = BSP_SOK;
    }

    return (retVal);
}

Int32 BspUtils_appDeInitUb960(UInt32 instId)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx;
    volatile UInt32 count;

    for (nIdx = 0U;
         nIdx < (sizeof (gUb960ResetCfg) / sizeof (gUb960ResetCfg[0U]));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            gSlaveAliases.slaveAddr,
            &(gUb960ResetCfg[nIdx].nRegAddr),
            &(gUb960ResetCfg[nIdx].nRegValue),
            (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure UB960 !!!\n");
            break;
        }

        if (0 != gUb960ResetCfg[nIdx].nDelay)
        {
            count = gUb960ResetCfg[nIdx].nDelay;
            while (count)
            {
                count--;
            }
        }
    }

    return (retVal);
}


Int32 BspUtils_appInitTida00262(UInt32 portId)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx;
    UInt32 i2cDevAddr;

    if (BSPUTILS_UB960EVM_MAX_PORTS > portId)
    {
        i2cDevAddr = gSlaveAliases.rSlave1Addr[portId];
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR,
                      "Wrong instance of TIDA00262 !!!\n");
        retVal = BSP_EFAIL;
    }
    for (nIdx = 0U;
         ((nIdx < (sizeof (gTida00262SerCfg) / sizeof (gTida00262SerCfg[0U]))) &&
          (BSP_SOK == retVal));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            i2cDevAddr,
            &(gTida00262SerCfg[nIdx].nRegAddr),
            &(gTida00262SerCfg[nIdx].nRegValue),
            (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure TIDA00262 !!!\n");
            break;
        }
    }

    return (retVal);
}


Int32 BspUtils_appDeInitTida00262(UInt32 portId)
{
    Int32   retVal = BSP_SOK;
    UInt32  nIdx;
    UInt32 i2cDevAddr;

    if (BSPUTILS_UB960EVM_MAX_PORTS > portId)
    {
        i2cDevAddr = gSlaveAliases.rSlave1Addr[portId];
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR,
                      "Wrong instance of TIDA00262 !!!\n");
        retVal = BSP_EFAIL;
    }
    for (nIdx = 0U;
         ((nIdx < (sizeof (gTida00262ResetCfg) / sizeof (gTida00262ResetCfg[0U]))) &&
          (BSP_SOK == retVal));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(
            UB960_ACCESSIBLE_FROM_I2C_INST,
            i2cDevAddr,
            &(gTida00262ResetCfg[nIdx].nRegAddr),
            &(gTida00262ResetCfg[nIdx].nRegValue),
            (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Could not configure TIDA00262 !!!\n");
            break;
        }
    }

    return (retVal);
}
