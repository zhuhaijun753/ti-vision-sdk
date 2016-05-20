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
 *  \file bspdrv_tvp7002I2c.c
 *
 *  \brief TVP7002 video decoder FVID2 driver implementation file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <tvp7002/src/bspdrv_tvp7002Priv.h>

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

static Int32 Bsp_tvp7002SetupVideo(const Bsp_Tvp7002HandleObj      *pObj,
                                   const Bsp_VidDecVideoModeParams *pPrm);
static Int32 Bsp_tvp7002SetOutputFormat(const Bsp_Tvp7002HandleObj      *pObj,
                                        const Bsp_VidDecVideoModeParams *pPrm);
static Int32 Bsp_tvp7002ApplyCsc(const Bsp_Tvp7002HandleObj *pObj,
                                 const UInt16               *cscCoeffs);
static Int32 Bsp_tvp7002PowerDown(const Bsp_Tvp7002HandleObj *pObj,
                                  UInt32                      powerDown);
static Int32 Bsp_tvp7002OutputEnable(const Bsp_Tvp7002HandleObj *pObj,
                                     UInt32                      enable);

static Int32 Bsp_tvp7002I2cRead8(const Bsp_Tvp7002HandleObj *pObj,
                                 UInt32                      i2cInstId,
                                 UInt32                      i2cDevAddr,
                                 const UInt8                *regAddr,
                                 UInt8                      *regVal,
                                 UInt32                      numRegs);
static Int32 Bsp_tvp7002I2cWrite8(const Bsp_Tvp7002HandleObj *pObj,
                                  UInt32                      i2cInstId,
                                  UInt32                      i2cDevAddr,
                                  const UInt8                *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                      numRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Resets the TVP7002.
 *
 *  This API
 *      - Disable output
 *      - Power-ON of all module
 *      - Manual reset of TVP7002 and then setup in auto reset mode
 */
Int32 Bsp_tvp7002Reset(const Bsp_Tvp7002HandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Disable outputs */
    retVal = Bsp_tvp7002Stop(pObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Device stop failed\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Normal operation */
        retVal = Bsp_tvp7002PowerDown(pObj, FALSE);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device power-up failed\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Gets TVP7002 Chip ID and revision ID.
 */
Int32 Bsp_tvp7002GetChipId(const Bsp_Tvp7002HandleObj   *pObj,
                           const Bsp_VidDecChipIdParams *pPrm,
                           Bsp_VidDecChipIdStatus       *pStatus)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr;
    UInt8  regVal;
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 i2cInstId;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pStatus) ||
        (NULL == pPrm) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, (UInt8) 0, sizeof (*pStatus));

        devAddr   = pObj->createPrms.deviceI2cAddr[0U];
        i2cInstId = pObj->createPrms.deviceI2cInstId;

        /* Read teh chip revision register */
        numRegs = 1U;
        regAddr = BSP_TVP7002_REG_CHIP_REVISION;
        regVal  = 0;
        retVal  = Bsp_tvp7002I2cRead8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr,
            &regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        /* Update status */
        pStatus->chipId          = 0x7002U;
        pStatus->chipRevision    = regVal;
        pStatus->firmwareVersion = 0U;
    }

    return (retVal);
}

/**
 *  \brief Sets the required video standard and output formats depending
 *  on requested parameters.
 */
Int32 Bsp_tvp7002SetVideoMode(Bsp_Tvp7002HandleObj            *pObj,
                              const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if (NULL == pPrm)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Reset device */
        retVal = Bsp_tvp7002Reset(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Device reset failed\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Setup video processing path based on request */
        retVal = Bsp_tvp7002SetupVideo(pObj, pPrm);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Setup video failed\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(&pObj->modePrms, pPrm, sizeof (pObj->modePrms));
    }

    return (retVal);
}

/**
 *  \brief Gets the video status of the detected video.
 */
Int32 Bsp_tvp7002GetVideoStatus(const Bsp_Tvp7002HandleObj        *pObj,
                                const Bsp_VidDecVideoStatusParams *pPrm,
                                Bsp_VidDecVideoStatus             *pStatus)
{
    Int32          retVal = FVID2_SOK;
    UInt8          regAddr[4U];
    UInt8          regVal[4U];
    UInt32         numRegs;
    UInt32         devAddr;
    UInt32         i2cInstId, delay;
    UInt32         clocksPerLine;
    Fvid2_ModeInfo modeInfo;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pStatus) || (NULL == pPrm))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }
    delay = 100U;
    BspOsal_sleep(delay);

    if (FVID2_SOK == retVal)
    {
        modeInfo.standard = pObj->modePrms.standard;
        if (FVID2_STD_AUTO_DETECT == modeInfo.standard)
        {
            /* For TVP7002 we assume 1080i60 for auto detect mode */
            modeInfo.standard = FVID2_STD_1080I_60;
        }

        retVal = Fvid2_getModeInfo(&modeInfo);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid standard!!\n");
        }
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_memset(pStatus, (UInt8) 0U, sizeof (*pStatus));

        devAddr   = pObj->createPrms.deviceI2cAddr[0U];
        i2cInstId = pObj->createPrms.deviceI2cInstId;

        numRegs     = 1U;
        regAddr[0U] = BSP_TVP7002_REG_SYNC_DETECT_STATUS;
        regVal[0U]  = 0;
        retVal      = Bsp_tvp7002I2cRead8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        /* Check for video detect */

        if (((Bool) ((UInt32) regVal[0U] & 0x02U)) ||
            (((Bool) ((UInt32) regVal[0U] & 0x80U)) &&
             ((Bool) ((UInt32) regVal[0U] & 0x10U))))
        {
            pStatus->isVideoDetect = TRUE;
        }
        else
        {
            pStatus->isVideoDetect = FALSE;
        }

        /* Read the other status registers */
        numRegs          = 0U;
        regAddr[numRegs] = BSP_TVP7002_REG_LINES_PER_FRAME_STATUS_LSB;
        regVal[numRegs]  = 0U;
        numRegs++;
        regAddr[numRegs] = BSP_TVP7002_REG_LINES_PER_FRAME_STATUS_MSB;
        regVal[numRegs]  = 0U;
        numRegs++;
        regAddr[numRegs] = BSP_TVP7002_REG_CLOCK_PER_LINE_STATUS_LSB;
        regVal[numRegs]  = 0U;
        numRegs++;
        regAddr[numRegs] = BSP_TVP7002_REG_CLOCK_PER_LINE_STATUS_MSB;
        regVal[numRegs]  = 0U;
        numRegs++;
        retVal = Bsp_tvp7002I2cRead8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr[0],
            &regVal[0],
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        clocksPerLine = (regVal[2U] | (((UInt32) regVal[3U] & 0x0FU) << 8U));

        /* Update the status information */
        pStatus->frameHeight =
            (regVal[0U] | (((UInt32) regVal[1U] & 0x0FU) << 8U));
        pStatus->isInterlaced = (UInt32) (!((Bool) ((UInt32) regVal[1U] & 0x20U)));

        /* Assuming 27MHz clock input */
        pStatus->frameWidth    = (clocksPerLine * modeInfo.pixelClock) / 27000U;
        pStatus->frameInterval = (clocksPerLine * pStatus->frameHeight) / 27U;
    }

    return (retVal);
}

/**
 *  \brief Starts TVP7002.
 */
Int32 Bsp_tvp7002Start(const Bsp_Tvp7002HandleObj *pObj)
{
    Int32 retVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Enable output */
    retVal = Bsp_tvp7002OutputEnable(pObj, (UInt32) TRUE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output enable failed\n");
    }

    return (retVal);
}

/**
 *  \brief Stops TVP7002.
 */
Int32 Bsp_tvp7002Stop(const Bsp_Tvp7002HandleObj *pObj)
{
    Int32 retVal;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Disable output */
    retVal = Bsp_tvp7002OutputEnable(pObj, FALSE);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Output disable failed\n");
    }

    return (retVal);
}

/**
 *  \brief Writes to device registers.
 */
Int32 Bsp_tvp7002RegWrite(const Bsp_Tvp7002HandleObj    *pObj,
                          const Bsp_VidDecRegRdWrParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt32 devAddr;
    UInt32 i2cInstId;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        devAddr   = pObj->createPrms.deviceI2cAddr[0U];
        i2cInstId = pObj->createPrms.deviceI2cInstId;
        retVal    = Bsp_tvp7002I2cWrite8(
            pObj,
            i2cInstId,
            devAddr,
            pPrm->regAddr,
            pPrm->regValue8,
            (Uint32) pPrm->numRegs);
    }

    return (retVal);
}

/**
 *  \brief Read from device registers.
 */
Int32 Bsp_tvp7002RegRead(const Bsp_Tvp7002HandleObj *pObj,
                         Bsp_VidDecRegRdWrParams    *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt32 devAddr;
    UInt32 i2cInstId;

    /* Check for errors */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if ((NULL == pPrm) ||
        (NULL == pPrm->regAddr) ||
        (NULL == pPrm->regValue8) ||
        (0U == pPrm->numRegs) ||
        (pPrm->deviceNum >= pObj->createPrms.numDevicesAtPort))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid arguments\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        devAddr   = pObj->createPrms.deviceI2cAddr[0U];
        i2cInstId = pObj->createPrms.deviceI2cInstId;

        BspUtils_memset(pPrm->regValue8, (UInt8) 0U, pPrm->numRegs);
        retVal = Bsp_tvp7002I2cRead8(
            pObj,
            i2cInstId,
            devAddr,
            &pPrm->regAddr[0],
            pPrm->regValue8,
            pPrm->numRegs);
    }

    return (retVal);
}

/**
 *  \brief Setup video modes.
 */
static Int32 Bsp_tvp7002SetupVideo(const Bsp_Tvp7002HandleObj      *pObj,
                                   const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32              retVal = FVID2_SOK;
    UInt32             numRegs;
    UInt32             devAddr;
    UInt32             i2cInstId;
    const UInt8       *regAddrList;
    static UInt8       regValList[sizeof (gTvp7002ModeAddrList)];
    Bsp_PlatformCpuRev cpuRev;
    Bsp_PlatformSocId  socId;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pPrm));

    /* Determine Platform and CPU version */
    socId  = Bsp_platformGetSocId();
    cpuRev = Bsp_platformGetCpuRev();
    if (((socId <= BSP_PLATFORM_ID_UNKNOWN) ||
         (socId >= BSP_PLATFORM_ID_MAX)) ||
        (cpuRev == BSP_PLATFORM_CPU_REV_UNKNOWN))
    {
        GT_assert(BspDeviceTrace, (FALSE));
    }

    if (FVID2_SOK == retVal)
    {
        devAddr   = pObj->createPrms.deviceI2cAddr[0U];
        i2cInstId = pObj->createPrms.deviceI2cInstId;

        /* Check for valid array sizes */
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002DefAddrList) == sizeof (gTvp7002DefValueList));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002Value1080p60EmbSync));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002Value1080i60EmbSync));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002Value720p60EmbSync));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002ValueSxga60));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002Value1080p60DiscSync));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002Value1080i60DiscSync));
        GT_assert(BspDeviceTrace,
                  sizeof (gTvp7002ModeAddrList) ==
                  sizeof (gTvp7002Value720p60DiscSync));

        regAddrList = &gTvp7002ModeAddrList[0];
        numRegs     = sizeof (gTvp7002ModeAddrList);

        /* Select the register values depending on standard */
        switch (pPrm->standard)
        {
            case FVID2_STD_1080P_60:
                if (pPrm->videoIfMode == FVID2_VIFM_SCH_DS_AVID_VSYNC)
                {
                    BspUtils_memcpy(regValList, gTvp7002Value1080p60DiscSync,
                                    numRegs);
                }
                else
                {
                    BspUtils_memcpy(regValList, gTvp7002Value1080p60EmbSync,
                                    numRegs);
                }
                break;

            case FVID2_STD_1080I_60:
            case FVID2_STD_AUTO_DETECT:
                if (pPrm->videoIfMode == FVID2_VIFM_SCH_DS_AVID_VSYNC)
                {
                    BspUtils_memcpy(regValList, gTvp7002Value1080i60DiscSync,
                                    numRegs);
                }
                else
                {
                    BspUtils_memcpy(regValList, gTvp7002Value1080i60EmbSync,
                                    numRegs);
                }
                break;

            case FVID2_STD_720P_60:
                if (pPrm->videoIfMode == FVID2_VIFM_SCH_DS_AVID_VSYNC)
                {
                    BspUtils_memcpy(regValList, gTvp7002Value720p60DiscSync,
                                    numRegs);
                }
                else
                {
                    BspUtils_memcpy(regValList, gTvp7002Value720p60EmbSync,
                                    numRegs);
                }
                break;

            case FVID2_STD_SXGA_60:
                BspUtils_memcpy(regValList, gTvp7002ValueSxga60, numRegs);
                break;

            default:
                retVal = FVID2_EINVALID_PARAMS;
                GT_0trace(BspDeviceTrace, GT_ERR, "Invalid standard\n");
                break;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Write the common settings for all the modes */
        retVal += Bsp_tvp7002I2cWrite8(
            pObj,
            i2cInstId,
            devAddr,
            gTvp7002DefAddrList,
            gTvp7002DefValueList,
            sizeof (gTvp7002DefAddrList));

        if (pPrm->videoIfMode == FVID2_VIFM_SCH_DS_AVID_VSYNC)
        {
            UInt32 idx;

            /* discrete sync mode, adjust AVID START, AVID END, VBLK START, VBLK
             *DURATION */
            for (idx = 0; idx < numRegs; idx++)
            {
                if (!(((socId == BSP_PLATFORM_SOC_ID_TI814X) &&
                       (cpuRev >= BSP_PLATFORM_CPU_REV_2_1)) ||
                      (socId == BSP_PLATFORM_SOC_ID_TI8149) ||
                      (socId == BSP_PLATFORM_SOC_ID_TI811X)))
                {
                    if ((regAddrList[idx] ==
                         BSP_TVP7002_REG_VBLK_FLD0_START_OFFSET) ||
                        (regAddrList[idx] ==
                         BSP_TVP7002_REG_VBLK_FLD1_START_OFFSET))
                    {
                        regValList[idx] = 0x0;
                    }
                    else if ((regAddrList[idx] ==
                              BSP_TVP7002_REG_VBLK_FLD0_DURATION) ||
                             (regAddrList[idx] ==
                              BSP_TVP7002_REG_VBLK_FLD1_DURATION))
                    {
                        regValList[idx] = 0x1;
                    }
                    else
                    {
                        /*Do Nothing*/
                    }
                }
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Write the mode specific settings */
            retVal += Bsp_tvp7002I2cWrite8(
                pObj,
                i2cInstId,
                devAddr,
                regAddrList,
                &regValList[0],
                numRegs);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Set the output format */
        retVal = Bsp_tvp7002SetOutputFormat(pObj, pPrm);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Set output format failed\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Setup output format.
 */
static Int32 Bsp_tvp7002SetOutputFormat(const Bsp_Tvp7002HandleObj      *pObj,
                                        const Bsp_VidDecVideoModeParams *pPrm)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr;
    UInt8  regVal;
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 i2cInstId;
    UInt32 order;
    UInt32 outFmt;
    UInt32 cscEnable;
    UInt32 isRgbInput;
    UInt32 codingRange;
    UInt32 embeddedSync;
    Bool   cscY2R;
    UInt32 regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != pPrm));

    devAddr   = pObj->createPrms.deviceI2cAddr[0U];
    i2cInstId = pObj->createPrms.deviceI2cInstId;

    order = BSP_TVP7002_CRCB_ORDER;
    if ((FVID2_DF_YUV422I_YVYU == pPrm->videoDataFormat) ||
        (FVID2_DF_YUV422I_VYUY == pPrm->videoDataFormat))
    {
        order = BSP_TVP7002_CBCR_ORDER;
    }

    if ((pPrm->standard >= FVID2_STD_VGA_60) &&
        (pPrm->standard <= FVID2_STD_UXGA_60))
    {
        /* VESA input */
        isRgbInput = (UInt32) TRUE;
    }
    else
    {
        /* YPbPr input */
        isRgbInput = FALSE;
    }

    outFmt = BSP_TVP7002_OUT_FORMAT_20BIT;

    cscEnable = FALSE;
    if ((UInt32) TRUE == isRgbInput)
    {
        cscEnable = (UInt32) TRUE;
    }

    codingRange  = BSP_TVP7002_RANGE_BT601;
    embeddedSync = (UInt32) TRUE;
    cscY2R       = (Bool) FALSE;

    switch (pPrm->videoDataFormat)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV422P:
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
            break;

        case FVID2_DF_YUV444P:
        case FVID2_DF_YUV444I:
            outFmt       = BSP_TVP7002_OUT_FORMAT_30BIT;
            embeddedSync = FALSE;
            break;

        case FVID2_DF_RGB24_888:
            outFmt    = BSP_TVP7002_OUT_FORMAT_30BIT;
            cscEnable = FALSE;
            if ((UInt32)FALSE == isRgbInput)
            {
                cscEnable = (UInt32) TRUE;
                cscY2R    = (Bool) TRUE;
            }
            codingRange  = BSP_TVP7002_RANGE_RGB;
            embeddedSync = FALSE;
            break;

        default:
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid data format\n");
            retVal = FVID2_EINVALID_PARAMS;
            break;
    }

    if (FVID2_SOK == retVal)
    {
        numRegs = 1U;
        regAddr = BSP_TVP7002_REG_OUT_FMT;

        regValue = ((codingRange << BSP_TVP7002_OUT_FMT_RANGE_SHIFT) |
                    (order << BSP_TVP7002_OUT_FMT_ORDER_SHIFT) |
                    (outFmt << BSP_TVP7002_OUT_FMT_DECIMATION_SHIFT) |
                    (embeddedSync << BSP_TVP7002_OUT_FMT_SYNC_ENABLE_SHIFT));
        regVal = (UInt8) regValue;

        retVal = Bsp_tvp7002I2cWrite8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr,
            &regVal,
            numRegs);
    }

    if (FVID2_SOK == retVal)
    {
        /* Read the out formatter register */
        numRegs = 1U;
        regAddr = BSP_TVP7002_REG_MISC_CTRL3;
        regVal  = 0;
        retVal  = Bsp_tvp7002I2cRead8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr,
            &regVal,
            numRegs);
        if (FVID2_SOK == retVal)
        {
            regValue  = (UInt32) regVal;
            regValue &= ~(BSP_TVP7002_MISC_CTRL3_CSC_ENABLE_MASK);
            regValue |= (cscEnable <<
                         BSP_TVP7002_MISC_CTRL3_CSC_ENABLE_SHIFT);
            regVal = (UInt8) regValue;

            /* Write the modified value */
            retVal = Bsp_tvp7002I2cWrite8(
                pObj,
                i2cInstId,
                devAddr,
                &regAddr,
                &regVal,
                numRegs);

            if (cscEnable)
            {
                #if 1
                if (cscY2R)
                {
                    /* Apply YUV444 to RGB888 CSC here */
                    Bsp_tvp7002ApplyCsc(pObj, gTvp7002CscCoeffYuv2Rgb);
                }
                else
                {
                    /* Apply RGB888 to YUV444 CSC here
                     * Apply default values in TVP7002
                     */
                    Bsp_tvp7002ApplyCsc(pObj, gTvp7002CscCoeffRgb2Yuv);
                }
                #endif
            }
        }
    }

    return (retVal);
}

static Int32 Bsp_tvp7002ApplyCsc(const Bsp_Tvp7002HandleObj *pObj,
                                 const UInt16               *cscCoeffs)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[BSP_TVP7002_NUM_CSC_COEFF_REGS];
    UInt8  regVal[BSP_TVP7002_NUM_CSC_COEFF_REGS];
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 i2cInstId, regId;

    devAddr   = pObj->createPrms.deviceI2cAddr[0U];
    i2cInstId = pObj->createPrms.deviceI2cInstId;

    for (regId = 0U; regId < BSP_TVP7002_NUM_CSC_COEFF_REGS; regId++)
    {
        regAddr[regId] = BSP_TVP7002_REG_CSC_COEFF0_LSB + (UInt8) regId;
        if ((regId % 2U) == 0)
        {
            /* LSB */
            regVal[regId] = ((UInt16) cscCoeffs[regId / 2U] >> 0) & 0xFFU;
        }
        else
        {
            /* MSB */
            regVal[regId] = ((UInt16) cscCoeffs[regId / 2U] >> 8U) & 0xFFU;
        }
    }
    numRegs = BSP_TVP7002_NUM_CSC_COEFF_REGS;

    retVal = Bsp_tvp7002I2cWrite8(
        pObj,
        i2cInstId,
        devAddr,
        &regAddr[0],
        &regVal[0],
        numRegs);

    return (retVal);
}

/**
 *  \brief Power ON/OFF TVP7002.
 */
static Int32 Bsp_tvp7002PowerDown(const Bsp_Tvp7002HandleObj *pObj,
                                  UInt32                      powerDown)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr;
    UInt8  regVal;
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 i2cInstId;
    UInt32 regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    devAddr   = pObj->createPrms.deviceI2cAddr[0U];
    i2cInstId = pObj->createPrms.deviceI2cInstId;

    numRegs = 1U;
    regAddr = BSP_TVP7002_REG_HPLL_CLAMP_CTRL;
    regVal  = 0;
    retVal  = Bsp_tvp7002I2cRead8(
        pObj,
        i2cInstId,
        devAddr,
        &regAddr,
        &regVal,
        numRegs);
    if (FVID2_SOK == retVal)
    {
        regValue = (UInt32) regVal;
        if ((UInt32) TRUE == powerDown)
        {
            regValue &= (~((UInt32) 0x20U));    /* Power down */
            regVal    = (UInt8) regValue;
        }
        else
        {
            regValue |= 0x02U;     /* Normal operation */
            regVal    = (UInt8) regValue;
        }

        retVal = Bsp_tvp7002I2cWrite8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr,
            &regVal,
            numRegs);
    }

    return (retVal);
}

/**
 *  \brief Enable output port.
 */
static Int32 Bsp_tvp7002OutputEnable(const Bsp_Tvp7002HandleObj *pObj,
                                     UInt32                      enable)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr;
    UInt8  regVal;
    UInt32 numRegs;
    UInt32 devAddr;
    UInt32 i2cInstId;
    UInt32 regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    devAddr   = pObj->createPrms.deviceI2cAddr[0U];
    i2cInstId = pObj->createPrms.deviceI2cInstId;

    numRegs = 1U;
    regAddr = BSP_TVP7002_REG_MISC_CTRL2;
    regVal  = 0;
    retVal  = Bsp_tvp7002I2cRead8(
        pObj,
        i2cInstId,
        devAddr,
        &regAddr,
        &regVal,
        numRegs);
    if (FVID2_SOK == retVal)
    {
        regValue = (UInt32) regVal;
        if ((UInt32) TRUE == enable)
        {
            regValue &= (~((UInt32) 0x01U));    /* Enable output */
            regVal    = (UInt8) regValue;
        }
        else
        {
            regValue |= 0x01U;     /* Disable output */
            regVal    = (UInt8) regValue;
        }

        retVal = Bsp_tvp7002I2cWrite8(
            pObj,
            i2cInstId,
            devAddr,
            &regAddr,
            &regVal,
            numRegs);
    }

    return (retVal);
}

/**
 *  \brief I2C read wrapper function.
 */
static Int32 Bsp_tvp7002I2cRead8(const Bsp_Tvp7002HandleObj *pObj,
                                 UInt32                      i2cInstId,
                                 UInt32                      i2cDevAddr,
                                 const UInt8                *regAddr,
                                 UInt8                      *regVal,
                                 UInt32                      numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

    retVal = Bsp_deviceRead8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C read failed\n");
    }

    return (retVal);
}

/**
 *  \brief I2C write wrapper function.
 */
static Int32 Bsp_tvp7002I2cWrite8(const Bsp_Tvp7002HandleObj *pObj,
                                  UInt32                      i2cInstId,
                                  UInt32                      i2cDevAddr,
                                  const UInt8                *regAddr,
                                  const UInt8                *regVal,
                                  UInt32                      numRegs)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regVal));

    retVal = Bsp_deviceWrite8(i2cInstId, i2cDevAddr, regAddr, regVal, numRegs);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "I2C write failed\n");
    }

    return (retVal);
}

