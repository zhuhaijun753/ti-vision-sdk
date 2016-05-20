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
 *  \file bsputils_lvds.c
 *
 *  \brief This file implements application level lvds related helper functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>
#include <stdint.h>
#include <hw_types.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <common/bsp_common.h>
#include <vps/vps_control.h>
#include <boards/bsp_board.h>
#include <i2c/bsp_i2c.h>
#include <devices/bsp_device.h>
#include <bsputils_app.h>
#include <bsputils_lvds.h>
#include <bsputils_mem.h>
#include <bsputils_prf.h>
#include <soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSPUTILS_MULDES_LOCK_CHECK_COUNT    (50U)
#define BSPUTILS_SER_RESET_CHECK_COUNT      (50U)

/* Sil9127 hdmi receiver Address */
#define BSPUTILS_SIL9127_ADDR           (0x31U)

#define BSPUTILS_MULTIDES_IO_EXP_ADDR_0 (0x27U)
#define BSPUTILS_MULTIDES_IO_EXP_ADDR_1 (0x21U)
#define BSPUTILS_MULTIDES_IO_EXP_ADDR_2 (0x25U)

/* Deserializers Addresses */
#ifdef TDA2XX_MC_BUILD
#define BSPUTILS_DES1_ADDR              (0x65U) /* 0xC0/2 */
#define BSPUTILS_DES2_ADDR              (0x6AU) /* 0xC8/2 */
#define BSPUTILS_DES3_ADDR              (0x6FU) /* 0xD0/2 */
#else
#define BSPUTILS_DES1_ADDR              (0x60U) /* 0xC0/2 */
#define BSPUTILS_DES2_ADDR              (0x64U) /* 0xC8/2 */
#define BSPUTILS_DES3_ADDR              (0x68U) /* 0xD0/2 */
#define BSPUTILS_DES4_ADDR              (0x6CU) /* 0xD8/2 */
#define BSPUTILS_DES5_ADDR              (0x61U) /* 0xC2/2 */
#define BSPUTILS_DES6_ADDR              (0x69U) /* 0xD2/2 */
#endif

/* Serializers addresses */
#define BSPUTILS_SER1_ALIAS_ADDR        (0x74U) /* 0xE8/2 */
#define BSPUTILS_SER2_ALIAS_ADDR        (0x75U) /* 0xEA/2 */
#define BSPUTILS_SER3_ALIAS_ADDR        (0x76U) /* 0xEC/2 */
#define BSPUTILS_SER4_ALIAS_ADDR        (0x77U) /* 0xEE/2 */
#define BSPUTILS_SER5_ALIAS_ADDR        (0x78U) /* 0xF0/2 */
#define BSPUTILS_SER6_ALIAS_ADDR        (0x79U) /* 0xF2/2 */

#define BSPUTILS_SER_ID_ADDR            (0x58U) /* 0xB0/2 */

/* Alias address of 6 OV sensors present in LVDS setup */
#define BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR   (0x38U) /* 0x70/2 */
#define BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR   (0x39U) /* 0x72/2 */
#define BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR   (0x3AU) /* 0x74/2 */
#define BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR   (0x3BU) /* 0x76/2 */
#define BSPUTILS_OV1063x_5_ALIAS_I2C_ADDR   (0x3CU) /* 0x78/2 */
#define BSPUTILS_OV1063x_6_ALIAS_I2C_ADDR   (0x3DU) /* 0x7A/2 */

#define BSPUTILS_OV1063x_I2C_ADDR       (0x30U)     /* 0x60/2 */

#ifdef TDA2XX_MC_BUILD
#define BSPUTILS_MAX_DES_SER_COUNT      (3U)
#else
#define BSPUTILS_MAX_DES_SER_COUNT      (6U)
#endif

/* Data Structures */
typedef struct
{
    UInt8 nRegAddr;
    UInt8 nRegValue;
} BspUtils_I2cParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 BspUtils_appConfSer(UInt32 devInstId, UInt32 i2cDevAddr);
static Int32 BspUtils_appConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr);

static Int32 BspUtils_appMultiDesIoExpConfig(UInt32 devInstId,
                                             UInt32 i2cDevAddr);

static Int32 BspUtils_appDeConfSer(UInt32 devInstId, UInt32 i2cDevAddr);
static Int32 BspUtils_appDeConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr);

static UInt32 BspUtils_appConvToOvInstId(UInt32 devInstId);

static Int32 BspUtils_appPrintReg(UInt32 i2cDevAddr, UInt8 nRegAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* By default disable SerDes de configuration */
static UInt32             gAppUtilsSerDesDeCfgEnable = FALSE;

static BspOsal_SemHandle  glockSem = NULL;

#ifdef TDA2XX_MC_BUILD
static UInt32             gSerDesCfgDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE
};
#else
static UInt32             gSerDesCfgDone[BSPUTILS_MAX_DES_SER_COUNT] =
{
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE
};
#endif

#ifdef TDA2XX_FAMILY_BUILD
/* i2c params for HDMI/I2C2 conflict removal */
static BspUtils_I2cParams gHdmiRecParams[] =
{
    {0x14, 0xF4},       /* SII9127 (?)   0x48->0x7A */
    {0x15, 0xF6},       /* SII9127 Color 0x32->0x7B */
    {0x16, 0xF8},       /* SII9127 (?)   0x68->0x7C */
    {0x17, 0xFA},       /* SII9127 (?)   0x73->0x7D */
    {0x18, 0xFC},       /* SII9127 CEC   0x60->0x7E */
    {0x19, 0xFE},       /* SII9127 EDID  0x70->0x7F */
};
#endif

static UInt32             gMulDesIoAddr[BSPUTILS_MAX_DES_SER_COUNT] =
{
#ifdef TDA2XX_MC_BUILD
    0,
    0,
    0,
#else
    BSPUTILS_MULTIDES_IO_EXP_ADDR_0,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_0,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_1,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_1,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_2,
    BSPUTILS_MULTIDES_IO_EXP_ADDR_2,
#endif
};

/* De-serializer addresses */
static UInt32             gDesAddr[BSPUTILS_MAX_DES_SER_COUNT] =
{
#ifdef TDA2XX_MC_BUILD
    BSPUTILS_DES1_ADDR,
    BSPUTILS_DES2_ADDR,
    BSPUTILS_DES3_ADDR,
#else
    BSPUTILS_DES1_ADDR,
    BSPUTILS_DES2_ADDR,
    BSPUTILS_DES3_ADDR,
    BSPUTILS_DES4_ADDR,
    BSPUTILS_DES5_ADDR,
    BSPUTILS_DES6_ADDR,
#endif
};

/* i2c params for multi-deserializer */
#ifdef TDA2XX_MC_BUILD
static BspUtils_I2cParams gMulDesParams[BSPUTILS_MAX_DES_SER_COUNT][7] =
{
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER1_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER2_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x1F, 0xF1                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER3_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR * 2U)},
    },
};
#else
static BspUtils_I2cParams gMulDesParams[BSPUTILS_MAX_DES_SER_COUNT][6] =
{
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER1_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_1_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER2_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_2_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER3_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_3_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER4_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_4_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER5_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_5_ALIAS_I2C_ADDR * 2U)},
    },
    {
        {0x01, 0x04                                    },
        {0x03, 0xEC                                    },
        {0x06, (BSPUTILS_SER_ID_ADDR * 2U)             },
        {0x08, (BSPUTILS_OV1063x_I2C_ADDR * 2U)        },
        {0x07, (BSPUTILS_SER6_ALIAS_ADDR * 2U)         },
        {0x10, (BSPUTILS_OV1063x_6_ALIAS_I2C_ADDR * 2U)},
    }
};
#endif

/* i2c params for Multi De-serializer i2c expander */
static BspUtils_I2cParams gI2cExpParams[BSPUTILS_MAX_DES_SER_COUNT][4] =
{
#ifdef TDA2XX_MC_BUILD
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
    },
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
#else
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
    },
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
    },
    {
        {0x00, 0x00},   /* IODIRA[7:0] - Output */
        {0x0C, 0x00},   /* GPPUA[7:0]  - Pull-up enabled */
        {0x12, 0x63},   /* GPIOA - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x12, 0xE3},   /* GPIOA - 7-PDB=1, Power-up */
    },
    {
        {0x01, 0x00},   /* IODIRB[7:0] - Output */
        {0x0D, 0x00},   /* GPPUB[7:0]  - Pull-up enabled */
        {0x13, 0x63},   /* GPIOB - 0:2-Mode,3-GPIO,4-BISTEN,5-OEN,6-SEL,7-PDB */
        {0x13, 0xE3}    /* GPIOB - 7-PDB=1, Power-up */
    },
#endif
};

/* i2c params for serializer */
static BspUtils_I2cParams gSerParams[] =
{
    {0x03, 0xC5},
    {0x0D, 0x55},
};

/* i2c de Configure params for serializer */
static BspUtils_I2cParams gSerDeCfgParams[] =
{
    {0x01, 0x33},
};

/* i2c de Configure params for multi-deserializer */
static BspUtils_I2cParams gMulDesDeCfgParams[] =
{
    {0x01, 0x24},
};

/**
 *  BspUtils_appInitSerDeSer
 *
 *  \brief BSP application utils function to setup board for LVDS Support.
 *  Sequence
 *  1. Removal of I2C Addr Conflict
 *  2. Configure all the IO Expanders in MULDES Board to configure De-Ser to
 *     operate In 10-bit mode, select input A etc.
 */
Int32 BspUtils_appInitSerDeSer(UInt32 devDrvId)
{
    Int32        retVal   = BSP_SOK;
    UInt32       nIoExpId = 0;
#ifdef TDA2XX_FAMILY_BUILD
    UInt32       i2cDevAddr;
    UInt32       nIdx;
    Bsp_BoardRev dcBoardRev;
#endif

    if (devDrvId == FVID2_VID_SENSOR_MULDES_OV1063X_DRV)
    {
        /* Assert if init is called twice with out deinit */
        GT_assert(BspAppTrace, (NULL == glockSem));
        glockSem = BspOsal_semCreate((Int32) 1, FALSE);
        if (NULL == glockSem)
        {
            GT_0trace(BspAppTrace, GT_ERR,
                      "Error: Semaphore create failed!!\n");
            retVal = BSP_EALLOC;
        }

        if (BSP_SOK == retVal)
        {
            BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

            GT_0trace(BspAppTrace, GT_INFO,
                      "Initializing Multi-Deserializer Setup ...!!\n");

#ifdef TDA2XX_FAMILY_BUILD
            dcBoardRev = Bsp_boardGetDcRev();
            /* SIL9127 not present in REV D VISION cards */
            if ((BSP_BOARD_MONSTERCAM != Bsp_boardGetId()) &&
                (dcBoardRev < BSP_BOARD_REV_D))
            {
                i2cDevAddr = BSPUTILS_SIL9127_ADDR;
                for (nIdx = 0U;
                     nIdx < (sizeof (gHdmiRecParams) /
                             sizeof (gHdmiRecParams[0U]));
                     nIdx++)
                {
                    UInt32 i2cInstId;

                    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
                    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
                    {
                        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
                    }

                    /* I2C write to remove I2C addr conflict with HDMI receiver
                     * - SIL9127 , present on Vision APP board */
                    retVal += Bsp_deviceWrite8(
                        i2cInstId,
                        i2cDevAddr,
                        &(gHdmiRecParams[nIdx].nRegAddr),
                        &(gHdmiRecParams[nIdx].nRegValue),
                        (UInt32) 1U);
                    if (retVal != BSP_SOK)
                    {
                        GT_0trace(BspAppTrace, GT_ERR,
                                  "I2C Addr Conflict Removal Failed!!\n");
                        break;
                    }
                }
            }
#endif
        }

        if (BSP_SOK == retVal)
        {
            if ((BSP_BOARD_MONSTERCAM != Bsp_boardGetId()))
            {
                /* Configure all the IO Expanders persent in MULDES Board */
                for (nIoExpId = 0;
                     nIoExpId <
                     (sizeof (gMulDesIoAddr) / sizeof (gMulDesIoAddr[0U]));
                     nIoExpId++)
                {
                    retVal = BspUtils_appMultiDesIoExpConfig(
                        nIoExpId,
                        gMulDesIoAddr[nIoExpId]);
                    if (retVal != BSP_SOK)
                    {
                        GT_0trace(
                            BspAppTrace, GT_ERR,
                            "Error: Configuring MutiDeserializer IO exp Failed!!\n");
                        break;
                    }
                }

                /* Sleep so that reset could happen */
                BspOsal_sleep((UInt32) 500U);
            }
        }

        if (NULL != glockSem)
        {
            BspOsal_semPost(glockSem);
        }
    }
    else
    {
        GT_0trace(BspAppTrace, GT_ERR, "Error: Invalid Driver ID!!\n");
        retVal = BSP_EINVALID_PARAMS;
    }

    return (retVal);
}

/**
 *  BspUtils_appDeInitSerDeSer
 *
 *  \brief BSP application utils function to undo stuff done in init.
 *  1. Deletion of semaphore created.
 */
Int32 BspUtils_appDeInitSerDeSer(UInt32 devDrvId)
{
    Int32 retVal = BSP_SOK;

    if (devDrvId == FVID2_VID_SENSOR_MULDES_OV1063X_DRV)
    {
        if (NULL != glockSem)
        {
            BspOsal_semDelete(&glockSem);
            glockSem = NULL;
        }
    }

    return retVal;
}

Int32 BspUtils_appDumpDeSerReg(UInt32 devDrvId, UInt32 devInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 serI2cDevAddr;
    UInt32 ovInstId;
    UInt8  cnt;

    if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR + ovInstId;
            for (cnt = 0U; cnt < 0x25U; cnt++)
            {
                BspUtils_appPrintReg(serI2cDevAddr, cnt);
                BspOsal_sleep((UInt32) 10U);
            }
        }
        else
        {
            retVal = BSP_EBADARGS;
        }

        BspOsal_semPost(glockSem);
    }
    else
    {
        retVal = BSP_EBADARGS;
    }

    return (retVal);
}

/**
 *  BspUtils_appConfSerDeSer
 *
 *  \brief BSP application utils function to Configure a particular instance of
 *  De-Serializer and serializer for LVDS Support.
 *  Sequence
 *  2. Configures a particular instance of Des with alias address of serializer
 *     and Ov sensor, enable I2C Pass through, enable I2C Auto Ack etc
 *  3. Configure a particular instace of Serializer in I2C pass through etc.
 */
Int32 BspUtils_appConfSerDeSer(UInt32 devDrvId, UInt32 devInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 serI2cDevAddr;
    UInt32 ovInstId;

    if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            if (FALSE == gSerDesCfgDone[ovInstId])
            {
                retVal = BspUtils_appConfMultiDeSer(
                    ovInstId,
                    gDesAddr[ovInstId]);
                if (BSP_SOK == retVal)
                {
                    serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR + ovInstId;
                    retVal        = BspUtils_appConfSer(ovInstId, serI2cDevAddr);
                }

                /* Sleep is required after Configuring
                 * each instance of multi deserializer and before accessing
                 * sensor */
                BspOsal_sleep((UInt32) 1000U);

                gSerDesCfgDone[ovInstId] = TRUE;
            }
        }
        else
        {
            retVal = BSP_EBADARGS;
        }

        BspOsal_semPost(glockSem);
    }
    else
    {
        retVal = BSP_EBADARGS;
    }

    return (retVal);
}

/**
 *  BspUtils_appDeConfSerDeSer
 *
 *  \brief BSP application utils function to De-Configure a particular instance
 *         of De-Serializer and serializer for LVDS Support.
 */
Int32 BspUtils_appDeConfSerDeSer(UInt32 devDrvId, UInt32 devInstId)
{
    Int32  retVal = BSP_SOK;
    UInt32 serI2cDevAddr;
    UInt32 ovInstId;

    if (FVID2_VID_SENSOR_MULDES_OV1063X_DRV == devDrvId)
    {
        BspOsal_semWait(glockSem, BSP_OSAL_WAIT_FOREVER);

        ovInstId = BspUtils_appConvToOvInstId(devInstId);
        if (ovInstId < BSPUTILS_MAX_DES_SER_COUNT)
        {
            if (((Bool) TRUE) == ((Bool) gAppUtilsSerDesDeCfgEnable))
            {
                serI2cDevAddr = BSPUTILS_SER1_ALIAS_ADDR + ovInstId;
                retVal        = BspUtils_appDeConfSer(ovInstId, serI2cDevAddr);
                if (BSP_SOK == retVal)
                {
                    retVal = BspUtils_appDeConfMultiDeSer(
                        ovInstId,
                        gDesAddr[ovInstId]);
                }

                /* Sleep is required after DeConfiguring
                 * each instance of multi deserializer */
                BspOsal_sleep((UInt32) 10U);

                gSerDesCfgDone[ovInstId] = FALSE;
            }
        }
        else
        {
            retVal = BSP_EBADARGS;
        }

        BspOsal_semPost(glockSem);
    }

    return (retVal);
}

/*  In Multi des board the connections are as shown below
 *
 *   CAM1 ---> VIN1A
 *   CAM2 ---> VIN2A
 *   CAM3 ---> VIN3A
 *   CAM4 ---> VIN5A
 *   CAM5 ---> VIN4B
 *   CAM6 ---> VIN6A
 *
 */
static UInt32 BspUtils_appConvToOvInstId(UInt32 devInstId)
{
    UInt32 ovInstId;

    switch (devInstId)
    {
        case BSP_DEVICE_MULDES_OV1063X_INST_ID_1:
            ovInstId = 0U;
            break;

        case BSP_DEVICE_MULDES_OV1063X_INST_ID_2:
            ovInstId = 1U;
            break;

        case BSP_DEVICE_MULDES_OV1063X_INST_ID_3:
            ovInstId = 2U;
            break;

        case BSP_DEVICE_MULDES_OV1063X_INST_ID_4:
            ovInstId = 3U;
            break;

        case BSP_DEVICE_MULDES_OV1063X_INST_ID_5:
            ovInstId = 4U;
            break;

        case BSP_DEVICE_MULDES_OV1063X_INST_ID_6:
            ovInstId = 5U;
            break;

        default:
            ovInstId = BSPUTILS_MAX_DES_SER_COUNT;
            break;
    }

    return (ovInstId);
}

static Int32 BspUtils_appConfSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt8  nRegAddr, nRegValue;
    UInt32 cnt = 0;
    UInt32 i2cInstId;

    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
    }
    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
    }

    /*
     * Reset serializer
     */
    nRegAddr  = 0x01U;
    nRegValue = 0x33U;
    retVal    = Bsp_deviceWrite8(
        i2cInstId,
        i2cDevAddr,
        &nRegAddr,
        &nRegValue,
        (UInt32) 1U);
    if (retVal != BSP_SOK)
    {
        GT_1trace(BspAppTrace, GT_ERR,
                  "Error: Failed to Configure ser for device 0x%x \n",
                  i2cDevAddr);
    }

    /* sleep needed to reset serializer */
    BspOsal_sleep((UInt32) 500U);

    if (BSP_SOK == retVal)
    {
        nRegAddr  = 0x01U;
        nRegValue = 0x00U;
        /* Checking the reset bit to get cleared */
        while (cnt < BSPUTILS_SER_RESET_CHECK_COUNT)
        {
            retVal = Bsp_deviceRead8(i2cInstId,
                                     i2cDevAddr,
                                     &nRegAddr,
                                     &nRegValue,
                                     (UInt32) 1U);
            if (retVal != FVID2_SOK)
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          " device address - %x i2c error - %d\n",
                          i2cDevAddr,
                          retVal);
                /* If I2C read fails re-try, don't exit!! */
            }

            if ((nRegValue & 0x03U) == 0U)
            {
                /* Reset done */
                retVal = FVID2_SOK;
                break;
            }

            /* sleep */
            BspOsal_sleep((UInt32) 10U);
            cnt++;
        }
        if (cnt == BSPUTILS_SER_RESET_CHECK_COUNT)
        {
            GT_1trace(BspAppTrace, GT_ERR,
                      " Ser reset failed - %x \n", i2cDevAddr);
            retVal = BSP_EFAIL;
        }
    }

    if (BSP_SOK == retVal)
    {
        for (nIdx = 0U;
             nIdx < (sizeof (gSerParams) / sizeof (gSerParams[0U]));
             nIdx++)
        {
            retVal += Bsp_deviceWrite8(i2cInstId,
                                       i2cDevAddr,
                                       &gSerParams[nIdx].nRegAddr,
                                       &gSerParams[nIdx].nRegValue,
                                       (UInt32) 1U);
            if (retVal != BSP_SOK)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "Error: Failed to Configure ser for device 0x%x \n",
                          i2cDevAddr);
                break;
            }

            /* sleep needed to reset serializer */
            BspOsal_sleep((UInt32) 10U);
        }
    }

    return (retVal);
}

static Int32 BspUtils_appDeConfSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt32 i2cInstId;

    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
    }
    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
    }

    for (nIdx = 0U;
         nIdx < (sizeof (gSerDeCfgParams) / sizeof (gSerDeCfgParams[0U]));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(i2cInstId,
                                  i2cDevAddr,
                                  &gSerDeCfgParams[nIdx].nRegAddr,
                                  &gSerDeCfgParams[nIdx].nRegValue,
                                  (UInt32) 1U);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to DeConfigure Ser for device 0x%x \n",
                i2cDevAddr);
            break;
        }

        /* sleep needed to reset serializer */
        BspOsal_sleep((UInt32) 10U);
    }

    return (retVal);
}

static Int32 BspUtils_appMultiDesIoExpConfig(UInt32 devInstId,
                                             UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt32 i2cInstId;

    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
    }
    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
    }

    for (nIdx = 0U;
         nIdx < (sizeof (gI2cExpParams[devInstId]) /
                 sizeof (gI2cExpParams[devInstId][0U]));
         nIdx++)
    {
        retVal += Bsp_deviceWrite8(i2cInstId,
                                   i2cDevAddr,
                                   &(gI2cExpParams[devInstId][nIdx].nRegAddr),
                                   &(gI2cExpParams[devInstId][nIdx].nRegValue),
                                   (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to Configure De-ser for device 0x%x \n",
                i2cDevAddr);
            break;
        }

        /* sleep so that reset could be performed */
        BspOsal_sleep((UInt32) 1U);
    }

    return (retVal);
}

static Int32 BspUtils_appDeConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal  = BSP_SOK;
    UInt32 nIdx    = 0;
    UInt32 numRegs = 1U;
    UInt32 i2cInstId;

    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
    }
    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
    }

    for (nIdx = 0U;
         nIdx < (sizeof (gMulDesDeCfgParams) / sizeof (gMulDesDeCfgParams[0U]));
         nIdx++)
    {
        retVal = Bsp_deviceWrite8(i2cInstId,
                                  i2cDevAddr,
                                  &(gMulDesDeCfgParams[nIdx].nRegAddr),
                                  &(gMulDesDeCfgParams[nIdx].nRegValue),
                                  numRegs);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to De-Configure De-ser for device 0x%x \n",
                i2cDevAddr);
            break;
        }

        /* sleep */
        BspOsal_sleep((UInt32) 10U);
    }

    return (retVal);
}

static Int32 BspUtils_appConfMultiDeSer(UInt32 devInstId, UInt32 i2cDevAddr)
{
    Int32  retVal = BSP_SOK;
    UInt32 nIdx   = 0;
    UInt8  nRegAddr, nRegValue;
    UInt32 cnt = 0;
    UInt32 i2cInstId;

    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
    }
    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
    }

    for (nIdx = 0U;
         nIdx <
         (sizeof (gMulDesParams[devInstId]) /
          sizeof (gMulDesParams[devInstId][0U]));
         nIdx++)
    {
        retVal += Bsp_deviceWrite8(i2cInstId,
                                   i2cDevAddr,
                                   &(gMulDesParams[devInstId][nIdx].nRegAddr),
                                   &(gMulDesParams[devInstId][nIdx].nRegValue),
                                   (UInt32) 1U);
        if (retVal != BSP_SOK)
        {
            GT_1trace(
                BspAppTrace, GT_ERR,
                "Error: Failed to Configure De-ser for device 0x%x \n",
                i2cDevAddr);
            break;
        }

        /* sleep */
        BspOsal_sleep((UInt32) 1U);
    }

    nRegAddr  = 0x06U;
    nRegValue = 0x0U;  /* Serializer ID */
    retVal    = Bsp_deviceRead8(i2cInstId,
                                i2cDevAddr,
                                &nRegAddr,
                                &nRegValue,
                                (UInt32) 1U);
    if (retVal != FVID2_SOK)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  " device address - %x i2c error - %d\n",
                  i2cDevAddr,
                  retVal);
    }

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Deser - %x - Address: 0x%x, Value: 0x%x\n",
              i2cDevAddr,
              nRegAddr, nRegValue);

    /* sleep */
    BspOsal_sleep((UInt32) 1U);

    nRegAddr  = 0x07U;
    nRegValue = 0x0U;  /* Serializer Alias */
    retVal    = Bsp_deviceRead8(i2cInstId,
                                i2cDevAddr,
                                &nRegAddr,
                                &nRegValue,
                                (UInt32) 1U);
    if (retVal != FVID2_SOK)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  " Device address - %x i2c error - %d\n",
                  i2cDevAddr,
                  retVal);
    }

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Deser - %x - Address: 0x%x, Value: 0x%x\n",
              i2cDevAddr,
              nRegAddr, nRegValue);

    /* sleep */
    BspOsal_sleep((UInt32) 1U);

    nRegAddr  = 0x1CU;
    nRegValue = 0x0U;
    /* Checking the Lock status */
    while (((nRegValue & 0x02U) == 0x0) &&
           (cnt < BSPUTILS_MULDES_LOCK_CHECK_COUNT))
    {
        retVal = Bsp_deviceRead8(i2cInstId,
                                 i2cDevAddr,
                                 &nRegAddr,
                                 &nRegValue,
                                 (UInt32) 1U);
        if (retVal != FVID2_SOK)
        {
            GT_2trace(BspAppTrace, GT_ERR,
                      " device address - %x i2c error - %d\n",
                      i2cDevAddr,
                      retVal);
        }
        cnt++;

        /* sleep */
        BspOsal_sleep((UInt32) 1U);
    }
    if (cnt >= BSPUTILS_MULDES_LOCK_CHECK_COUNT)
    {
        GT_1trace(BspAppTrace, GT_ERR,
                  " DE-Ser and Ser Link is not up for addr - %x \n",
                  i2cDevAddr);
        retVal = BSP_EFAIL;
    }

    GT_3trace(BspAppTrace, GT_DEBUG,
              " Deser - %x - Address: 0x%x, Value: 0x%x\n",
              i2cDevAddr,
              nRegAddr, nRegValue);

    return (retVal);
}

static Int32 BspUtils_appPrintReg(UInt32 i2cDevAddr, UInt8 nRegAddr)
{
    Int32  retVal = BSP_SOK;
    UInt8  nRegValue;
    UInt32 i2cInstId;

    i2cInstId = BSP_DEVICE_I2C_INST_ID_1;
    if (BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_4;
    }
    if (BSP_BOARD_MONSTERCAM == Bsp_boardGetId())
    {
        i2cInstId = BSP_DEVICE_I2C_INST_ID_2;
    }

    nRegValue = 0x0U;
    retVal    = Bsp_deviceRead8(i2cInstId,
                                i2cDevAddr,
                                &nRegAddr,
                                &nRegValue,
                                (UInt32) 1U);
    if (retVal != FVID2_SOK)
    {
        GT_2trace(BspAppTrace, GT_ERR,
                  " device address - %x i2c error - %d\n",
                  i2cDevAddr, retVal);
    }
    GT_3trace(BspAppTrace, GT_INFO,
              " Device (0x%0.2x) Offset: 0x%0.2x, Value: 0x%0.2x\n",
              i2cDevAddr, nRegAddr, nRegValue);

    return (retVal);
}

