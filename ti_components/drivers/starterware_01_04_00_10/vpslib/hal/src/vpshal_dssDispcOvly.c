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
 *  \file vpshal_dssDispcOvly.c
 *
 *  \brief VPS DSS Dispc Overlay  HAL file.
 *  This file implements the HAL APIs of the DSS DISPC Overlay.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>

#include <hw_types.h>
#include <hw_dispc.h>
#include <hw_dss_family.h>
#include <soc.h>
#include <fvid2/fvid2_dataTypes.h>
#include <vps/vps_dataTypes.h>
#include <vps/vps_cfgDss.h>
#include <vps/vps_displayCtrlDataTypes.h>
#include <hal/vpshal.h>
#include <hal/vpshal_dssDispcOvly.h>

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DssDispcOvlyRegOffset
 *  \brief structure to store register offsets of each Overlay.
 */
typedef struct
{
    UInt32 dispcControl;
    /**<  offset of Control register for an instance*/
    UInt32 dispcConfig;
    /**<  offset of Config register for an instance*/
    UInt32 defaultcolor;
    /**<  offset of Default Color register for an instance*/
    UInt32 panelSize;
    /**<  offset of panel size register for an instance*/
    UInt32 pipeAttrib[4];
    /**<  Array of offset of attribute register for an instance*/
    UInt32 cprCoeff[3];
    /**<  Array of offset of CPR coefficients register for an instance*/
    UInt32 globalAlpha;
    /**<  offset of global alpha register for an instance*/
    UInt32 transColor;
    /**<  offset of trans color register for an instance*/
    UInt32 dataCycle1;
    /**<  offset of Tdm Data1 Cycle register for an instance*/
    UInt32 dataCycle2;
    /**<  offset of Tdm Data2 Cycle register for an instance*/
    UInt32 dataCycle3;
    /**<  offset of Tdm Data3 Cycle register for an instance*/
    UInt32 polFreq;
    /**<  offset of Pol  register for an instance*/
    UInt32 lcdTimingH;
    /**<  offset of horizontal Lcd Timing  register for an instance*/
    UInt32 lcdTimingV;
    /**<  offset of vertical Lcd Timing  register for an instance*/
    UInt32 lcdDivisor;
    /**<  offset of divior register for generating the freq for an instance*/
    UInt32 lineStatus;
    /**<  offset of Line status register to get the current line number for an
     *    instance*/
} VpsHal_DssDispcOvlyRegOffset;

/**
 *  struct VpsHal_DssDispcOvlyObj
 *  \brief Per instance information about each Overlay  module.
 */
typedef struct
{
    UInt32                       halId;
    /**< Instance number/ID */
    UInt32                       openCnt;
    /**< Counter to keep track of number of open calls for an instance */
    UInt32                       dispcBaseAddr;
    /**< DISPC Base address. */
    UInt32                       dssBaseAddr;
    /**< DSS Family Base address. */
    VpsHal_DssDispcOvlyRegOffset regOffset;
    /**< Structure to store offsets of all the registers related to Overlay */
} VpsHal_DssDispcOvlyObj;

/* RGB to YUV conversion info */
typedef struct
{
    Int16 rr, rg, rb;
    Int16 gr, gg, gb;
    Int16 br, bg, bb;
} VpsHal_DssDispcCprCoeff;

Fvid2_ModeInfo gDssStdModeInfo[] = {
    {FVID2_STD_1080P_60,       1920, 1080, FVID2_SF_PROGRESSIVE, 148500, 60,
     88, 148, 44, 4, 36, 5},
    {FVID2_STD_1080P_50,       1920, 1080, FVID2_SF_PROGRESSIVE, 74250,  50,
     528, 148, 44, 4, 36, 5},
    {FVID2_STD_1080P_30,       1920, 1080, FVID2_SF_PROGRESSIVE, 74250,  30,
     88, 148, 44, 4, 36, 5},
    {FVID2_STD_720P_60,        1280, 720,  FVID2_SF_PROGRESSIVE, 74250,  60,
     110, 220, 40, 5, 20, 5},
    {FVID2_STD_720P_50,        1280, 720,  FVID2_SF_PROGRESSIVE, 74250,  50,
     440, 220, 40, 5, 20, 5},
    {FVID2_STD_XGA_60,         1024, 768,  FVID2_SF_PROGRESSIVE, 65000,  60,
     24, 160, 136, 3, 29, 6},
    {FVID2_STD_XGA_DSS_TDM_60, 1024, 768,  FVID2_SF_PROGRESSIVE, 64000,  60,
     136, 160, 24, 3, 29, 6},
    {FVID2_STD_XGA_75,         1024, 768,  FVID2_SF_PROGRESSIVE, 78750,  75,
     16, 176, 96, 1, 28, 3},
    {FVID2_STD_SXGA_60,        1280, 1024, FVID2_SF_PROGRESSIVE, 108000, 60,
     48, 248, 112, 1, 38, 3},
    {FVID2_STD_SXGA_75,        1280, 1024, FVID2_SF_PROGRESSIVE, 135000, 75,
     16, 248, 144, 1, 38, 3},
    {FVID2_STD_UXGA_60,        1600, 1200, FVID2_SF_PROGRESSIVE, 162000, 60,
     64, 304, 192, 1, 46, 3},
    {FVID2_STD_1080I_60,       1920, 1080, FVID2_SF_INTERLACED,  74250,  30,
     88, 148, 44, 2, 15, 5},
    {FVID2_STD_1080I_50,       1920, 1080, FVID2_SF_INTERLACED,  74250,  30,
     528, 148, 44, 2, 15, 5},
    {FVID2_STD_480P,           720,  480,  FVID2_SF_PROGRESSIVE, 27000,  60,
     16, 60, 62, 9, 30, 6},
    {FVID2_STD_576P,           720,  576,  FVID2_SF_PROGRESSIVE, 27000,  50,
     12, 68, 64, 5, 39, 5},
    {FVID2_STD_576I,           720,  576,  FVID2_SF_INTERLACED,  27000,  25,
     12, 69, 63, 2, 19, 3},
    {FVID2_STD_480I,           720,  480,  FVID2_SF_INTERLACED,  27000,  30,
     19, 57, 62, 4, 15, 3},
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 halDispcOvlyInitInstance(VpsHal_DssDispcOvlyObj *dispcOvlyObj);

static void halDispcOvlyPipeConfZorder(VpsHal_Handle handle,
                                       UInt32        pipe,
                                       UInt32        zorder,
                                       UInt32        zorderEnable);

static void halDispcOvlyPipeSetGlobalAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        globalAlpha);

static void halDispcOvlyPipeSetPreMulAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        preMultiplyAlpha);

static void halDispcOvlyPipeSetChannelOut(VpsHal_Handle handle,
                                          UInt32        pipe);

static void halDispcOvlyPanelColorKeyConf(VpsHal_Handle handle,
                                          UInt32        colorKeyEnable,
                                          UInt32        colorKeySel);

static void halDispcOvlyPanelSetTransColorKey(VpsHal_Handle handle,
                                              UInt32        transColorKey);

static void halDispcOvlyPanelDeltaLinesConf(VpsHal_Handle handle,
                                            UInt32        deltaLinesPerPanel);

static void halDispcOvlySetBgColor(VpsHal_Handle handle,
                                   UInt32        bgColor);

static void halDispcOvlyAlphaBlenderConf(VpsHal_Handle handle,
                                         UInt32        alphaBlenderEnable);

static void halDispcOvlyOptimizationConf(VpsHal_Handle handle,
                                         UInt32        ovlyOptimization);

static void halDispcOvlyGetChannelOutVal(UInt32  halId,
                                         UInt32 *chlout,
                                         UInt32 *chlout2);
static void halDispcConfCprCoeff(VpsHal_Handle handle);

static Int32 halDispcOvlyBT656_1120Conf(VpsHal_Handle handle,
                                        UInt32        dvoFormat,
                                        UInt32        enable);

static void halDispcReset(void);

static void halDispcFclkDivSet(void);

static void halDispcSetDefIntfWidth(void);

static void halDispcDisableMstandbyEnhancement(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  DISP OVL  objects - Module variable to store information about each Overlay
 *  instance .Note: If the number of Overlay  instance increase,
 *  then VPSHAL_DSS_DISPC_OVLY_MAX_INST macro should be changed accordingly.
 */
static VpsHal_DssDispcOvlyObj gDispcOvlyHalObj[VPSHAL_DSS_DISPC_OVLY_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_dssOvlyInit
 *  \brief DISPC OVL HAL init function.
 *
 *  Initializes OVL objects, gets the register overlay offsets for DISPC OVL
 *  registers.
 *  This function should be called before calling any of DISPC OVL HAL API's.
 *
 *  \param numInst          Number of instance objects to be initialized
 *  \param instPrms         Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *                          This parameter should not be NULL.
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyInit(UInt32                            numInst,
                         const VpsHal_DispcOvlyInstParams *instPrms,
                         Ptr                               arg)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, numInst <= VPSHAL_DSS_DISPC_OVLY_MAX_INST);
    GT_assert(VpsHalTrace, instPrms != NULL);

    /* Initialize DISPC OVL Objects to zero */
    BspUtils_memset(gDispcOvlyHalObj, 0, sizeof (gDispcOvlyHalObj));

    for (instCnt = 0; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  instPrms[instCnt].halId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX);

        dispcOvlyObj                = &gDispcOvlyHalObj[instCnt];
        dispcOvlyObj->halId         = instPrms[instCnt].halId;
        dispcOvlyObj->dispcBaseAddr = SOC_DISPC_BASE;
        dispcOvlyObj->dssBaseAddr   = SOC_DSS_FAMILY_BASE;

        /* Initialize the instance */
        retVal += halDispcOvlyInitInstance(dispcOvlyObj);
    }

    halDispcReset();

    VpsHal_dssDefaultParalleSelect();

    halDispcFclkDivSet();

    halDispcSetDefIntfWidth();

    /* Errata-  i815 - Power Management Enhancement Implemented Inside DSS
     * leads to DSS Underflows. Setting DISABLE_MSTANDBY_ENHANCEMENT[0] prevents
     * the occurrence of this bug. Applicable for tda2xx and tda2ex
     */
    halDispcDisableMstandbyEnhancement();

    return (retVal);
}

/**
 *  VpsHal_dssOvlyDeInit
 *  \brief DSS DISPC OVL HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyDeInit(Ptr arg)
{
    UInt32 instCnt;

    for (instCnt = 0; instCnt < VPSHAL_DSS_DISPC_OVLY_MAX_INST; instCnt++)
    {
        gDispcOvlyHalObj[instCnt].halId   = 0;
        gDispcOvlyHalObj[instCnt].openCnt = 0;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_dssDefaultParalleSelect
 *  \brief Default select Mux 13 value.
 *
 *  By default, the input to DPI is TV input, which shows HDMI output on
 *  LCD too. To solve that, initialize the mux to have a default value of
 *  LCD1.
 *
 *  \param                 None
 *
 *  \return                 Returns BSP_SOK on success
 */

Int32 VpsHal_dssDefaultParalleSelect(void)
{
    HW_WR_FIELD32(
        SOC_DSS_FAMILY_BASE + DSS_CTRL,
        DSS_CTRL_PARALLEL_SEL,
        DSS_CTRL_PARALLEL_SEL_LCD1);

    return (BSP_SOK);
}

/**
 *  VpsHal_dssOvlyOpen
 *  \brief Returns the handle to the requested DISPC OVL(Overlay) instance.
 *
 *  This function should be called prior to calling any of the DISPC OVL HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param halId            Requested DISPC OVL instance.
 *
 *  \return                 Returns DISPC OVL instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_dssOvlyOpen(const VpsHal_DispcOvlyOpenParams *openPrms)
{
    UInt32        cnt;
    VpsHal_Handle handle = NULL;

    /* Check if instance number is valid */
    GT_assert(VpsHalTrace, NULL != openPrms);
    GT_assert(VpsHalTrace,
              openPrms->halId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX);

    for (cnt = 0; cnt < VPSHAL_DSS_DISPC_OVLY_MAX_INST; cnt++)
    {
        /* Return the matching instance handle */
        if (openPrms->halId == gDispcOvlyHalObj[cnt].halId)
        {
            /* Check whether some one has already opened this instance */
            if (0U == gDispcOvlyHalObj[cnt].openCnt)
            {
                handle = (VpsHal_Handle) & gDispcOvlyHalObj[cnt];
                gDispcOvlyHalObj[cnt].openCnt++;
            }
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_dssOvlyClose
 *  \brief Closes the DISPC OVL HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyClose(VpsHal_Handle handle)
{
    Int32 retVal = BSP_EFAIL;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    /* Decrement the open count */
    if (dispcOvlyObj->openCnt > 0U)
    {
        dispcOvlyObj->openCnt--;
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlySetGoBit
 *  \brief GO command for the Overlay output. It is used to
 *   synchronized the pipelines (graphics and/or video ones)
 *   associated with the overlay output..
 *
 *  This function will Set the Go Bit of the overlay
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetGoBit(UInt32 ovlyId)
{
    Int32 retVal = BSP_SOK;

    if (ovlyId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if (ovlyId == VPSHAL_DSS_DISPC_LCD1)
        {
            HW_WR_FIELD32(
                SOC_DISPC_BASE + DSS_DISPC_CONTROL1,
                DSS_DISPC_CONTROL1_GOLCD,
                1U);
        }
        else if (ovlyId == VPSHAL_DSS_DISPC_LCD2)
        {
            HW_WR_FIELD32(
                SOC_DISPC_BASE + DSS_DISPC_CONTROL2,
                DSS_DISPC_CONTROL2_GOLCD,
                1U);
        }
        else if (ovlyId == VPSHAL_DSS_DISPC_LCD3)
        {
            HW_WR_FIELD32(
                SOC_DISPC_BASE + DSS_DISPC_CONTROL3,
                DSS_DISPC_CONTROL3_GOLCD,
                1U);
        }
        else if (ovlyId == VPSHAL_DSS_DISPC_HDMI)
        {
            HW_WR_FIELD32(
                SOC_DISPC_BASE + DSS_DISPC_CONTROL1,
                DSS_DISPC_CONTROL1_GOTV,
                1U);
        }
        else
        {
            retVal = BSP_EBADARGS;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyGetGoBit
 *  \brief Returns the Value of the GoBit.
 *
 *  This function will Return the status of the Go bit.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param bitVal           Pointer to a variable, varialbe is set to 0 if the
 *                          previous applied configuration by the software is
 *                          accepted by hardware.sets to 1 if Its not accepted.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetGoBit(VpsHal_Handle handle, UInt32 *bitVal)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != bitVal);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if (dispcOvlyObj->halId == VPSHAL_DSS_DISPC_HDMI)
        {
            *bitVal =
                HW_RD_FIELD32(
                    dispcOvlyObj->regOffset.dispcControl,
                    DSS_DISPC_CONTROL1_GOTV);
        }
        else
        {
            *bitVal =
                HW_RD_FIELD32(
                    dispcOvlyObj->regOffset.dispcControl,
                    DSS_DISPC_CONTROL1_GOLCD);
        }
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyEnable
 *  \brief Configures the Video/Gfx pipeline params related to overlay.
 *
 *  This function will enable or disable the overlay
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param enable           enable or disable the Overlay
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnable(VpsHal_Handle handle,
                           UInt32        enable)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if (dispcOvlyObj->halId == VPSHAL_DSS_DISPC_HDMI)
        {
            HW_WR_FIELD32(
                dispcOvlyObj->regOffset.dispcControl,
                DSS_DISPC_CONTROL1_TVENABLE,
                enable);
        }
        else
        {
            HW_WR_FIELD32(
                dispcOvlyObj->regOffset.dispcControl,
                DSS_DISPC_CONTROL1_LCDENABLE,
                enable);
        }
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyPipeConfig
 *  \brief Configures the Video/Gfx pipeline params related to overlay.
 *
 *  This function will configure the pipeline parameters like to which overlay
 *  the pipeline should be connected to, z-order of displays, globalalpha and
 *  premultiply alpha
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param pipeCfg          Pointer to the Overlay Pipe config structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyPipeConfig(VpsHal_Handle                     handle,
                               const Vps_DssDispcOvlyPipeConfig *pipeCfg)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != pipeCfg);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }

    if (pipeCfg->pipeLine >= VPS_DSS_DISPC_PIPE_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Pipeline\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        halDispcOvlyPipeConfZorder(
            handle,
            pipeCfg->pipeLine,
            pipeCfg->zorder,
            pipeCfg->zorderEnable);

        halDispcOvlyPipeSetGlobalAlpha(
            handle,
            pipeCfg->pipeLine,
            pipeCfg->globalAlpha);

        halDispcOvlyPipeSetPreMulAlpha(
            handle,
            pipeCfg->pipeLine,
            pipeCfg->preMultiplyAlpha);

        halDispcOvlyPipeSetChannelOut(handle, pipeCfg->pipeLine);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyPanelConf
 *  \brief Configures the overlay.
 *
 *  This function will configure the pipeline parameters like to which overlay
 *  the pipeline should be connected to, z-order of displays, globalalpha and
 *  premultiply alpha
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param pipeConf         Pointer to the Overlay Pipe config structure.
 *                          This parameter should not be NULL.
 *  \param pipe             This specifies to which pipe this configuration
 *                          should be applied to
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyPanelConf(
    VpsHal_Handle                      handle,
    const Vps_DssDispcOvlyPanelConfig *panelConfig)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != panelConfig);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        halDispcOvlyPanelColorKeyConf(
            handle,
            panelConfig->colorKeyEnable,
            panelConfig->colorKeySel);

        halDispcOvlyPanelSetTransColorKey(handle, panelConfig->transColorKey);

        halDispcOvlyPanelDeltaLinesConf(
            handle,
            panelConfig->deltaLinesPerPanel);

        halDispcOvlySetBgColor(handle, panelConfig->backGroundColor);

        halDispcOvlyAlphaBlenderConf(handle, panelConfig->alphaBlenderEnable);

        halDispcOvlyOptimizationConf(handle, panelConfig->ovlyOptimization);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdAdvDispConfig
 *  \brief Configures the Advance LCD Overlay Display Params.
 *
 *  This function will configures Advance LCD Overlays Display parameters, like
 *  Stall Mode, number of data lines, fid sequence.
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTdmConfig     Pointer to the LCD Overlay Advance Display Param
 *                          structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdAdvDispConfig(
    VpsHal_Handle                          handle,
    const Vps_DssDispcLcdAdvDisplayConfig *lcdAdvDisplay)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdAdvDisplay);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write CONFIG1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcConfig);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_FIDFIRST,
            lcdAdvDisplay->fidFirst);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_BUFFERHANDCHECK,
            lcdAdvDisplay->buffHandCheck);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcConfig, regVal);

        /* write CONTROL1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcControl);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_STALLMODE,
            lcdAdvDisplay->stallModeEnable);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_M8B,
            lcdAdvDisplay->mono8bit);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_STNTFT,
            lcdAdvDisplay->stnTft);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_MONOCOLOR,
            lcdAdvDisplay->monoColor);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcControl, regVal);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdTdmConfig
 *  \brief Configures the LCD TDM(Time division multiplexing) Params.
 *
 *  This function will configures LCD Overlay's TDM parameters, like Number of
 *  bits per each cycle, bit alignment for all pixels.
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTdmConfig     Pointer to the LCD Overlay TDM Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdTdmConfig(
    VpsHal_Handle                      handle,
    const Vps_DssDispcAdvLcdTdmConfig *lcdTdmConfig)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdTdmConfig);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write DATA1_CYCLE1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dataCycle1);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1,
            lcdTdmConfig->noBitsPixel1Cycle1);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1,
            lcdTdmConfig->bitAlignPixel1Cycle1);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2,
            lcdTdmConfig->noBitsPixel2Cycle1);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2,
            lcdTdmConfig->bitAlignPixel2Cycle1);
        HW_WR_REG32(dispcOvlyObj->regOffset.dataCycle1, regVal);

        /* write DATA1_CYCLE2 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dataCycle2);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1,
            lcdTdmConfig->noBitsPixel1Cycle2);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1,
            lcdTdmConfig->bitAlignPixel1Cycle2);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2,
            lcdTdmConfig->noBitsPixel2Cycle2);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2,
            lcdTdmConfig->bitAlignPixel2Cycle2);
        HW_WR_REG32(dispcOvlyObj->regOffset.dataCycle2, regVal);

        /* write DATA1_CYCLE3 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dataCycle3);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1,
            lcdTdmConfig->noBitsPixel1Cycle3);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1,
            lcdTdmConfig->bitAlignPixel1Cycle3);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2,
            lcdTdmConfig->noBitsPixel2Cycle3);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2,
            lcdTdmConfig->bitAlignPixel2Cycle3);
        HW_WR_REG32(dispcOvlyObj->regOffset.dataCycle3, regVal);

        /* write CONTROL1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcControl);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_TDMUNUSEDBITS,
            lcdTdmConfig->tdmUnusedBits);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_TDMCYCLEFORMAT,
            lcdTdmConfig->tdmCycleFormat);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_TDMPARALLELMODE,
            lcdTdmConfig->tdmParallelMode);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_TDMENABLE,
            lcdTdmConfig->tdmEnable);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcControl, regVal);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdConfLineNum
 *  \brief Set the LineNumber at which the interrupt should be generated
 *
 *  This function will configures set the Line number in the overlay
 *  when the display reaches this line it will generate the Interrupt.
 *
 *  \param handle        Valid handle returned by VpsHal_dssOvlyOpen
 *                       function
 *  \param lineNum       Line Number that should be programmed in the register .
 *
 *  \return              Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdConfLineNum(
    VpsHal_Handle handle,
    UInt32        lineNum)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId != VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not applicable for Hal instance other than LCD1\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_LINE_NUMBER, lineNum);
    }

    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdSetTiming
 *  \brief Configures the LCD Timing Params.
 *
 *  This function will configures LCD Overlay Timing Parameters, like front
 *  porch, back porch , divider values
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTimingParm    Pointer to the LCD Timing Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSetTiming(
    VpsHal_Handle                  handle,
    VpsHal_DssDispcLcdTimingParam *lcdTimingParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal, numStdModes, modeCnt;
    VpsHal_DssDispcLcdTimingParam vpTimingParm;
    UInt32 tdmRegVal, tdmCycleFormat, tdmEnable;
    UInt32 hBlankMultFact, hBlankDivFact;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdTimingParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if (FVID2_STD_CUSTOM != lcdTimingParm->standard)
    {
        numStdModes = sizeof (gDssStdModeInfo) / sizeof (Fvid2_ModeInfo);

        for (modeCnt = 0U; modeCnt < numStdModes; modeCnt++)
        {
            if (lcdTimingParm->standard == gDssStdModeInfo[modeCnt].standard)
            {
                vpTimingParm.width       = gDssStdModeInfo[modeCnt].width;
                vpTimingParm.height      = gDssStdModeInfo[modeCnt].height;
                vpTimingParm.hFrontPorch = gDssStdModeInfo[modeCnt].hFrontPorch;
                vpTimingParm.hBackPorch  = gDssStdModeInfo[modeCnt].hBackPorch;
                vpTimingParm.hSyncLen    = gDssStdModeInfo[modeCnt].hSyncLen;
                vpTimingParm.vFrontPorch = gDssStdModeInfo[modeCnt].vFrontPorch;
                vpTimingParm.vBackPorch  = gDssStdModeInfo[modeCnt].vBackPorch;
                vpTimingParm.vSyncLen    = gDssStdModeInfo[modeCnt].vSyncLen;

                /* Width and height is copied as this will be used by core for
                 * standard resolutions. */
                lcdTimingParm->width  = gDssStdModeInfo[modeCnt].width;
                lcdTimingParm->height = gDssStdModeInfo[modeCnt].height;

                if (gDssStdModeInfo[modeCnt].scanFormat == FVID2_SF_INTERLACED)
                {
                    vpTimingParm.scanFormat = 1;
                }
                else
                {
                    vpTimingParm.scanFormat = 0;
                }

                break;
            }
        }
        if (modeCnt == numStdModes)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Mode not supported \n");
            retVal = BSP_EBADARGS;
        }
    }
    else
    {
        vpTimingParm.width       = lcdTimingParm->width;
        vpTimingParm.height      = lcdTimingParm->height;
        vpTimingParm.hFrontPorch = lcdTimingParm->hFrontPorch;
        vpTimingParm.hBackPorch  = lcdTimingParm->hBackPorch;
        vpTimingParm.hSyncLen    = lcdTimingParm->hSyncLen;
        vpTimingParm.vFrontPorch = lcdTimingParm->vFrontPorch;
        vpTimingParm.vBackPorch  = lcdTimingParm->vBackPorch;
        vpTimingParm.vSyncLen    = lcdTimingParm->vSyncLen;
        if (lcdTimingParm->scanFormat == FVID2_SF_INTERLACED)
        {
            vpTimingParm.scanFormat = 1;
        }
        else
        {
            vpTimingParm.scanFormat = 0;
        }
    }

    if (retVal == BSP_SOK)
    {
        /* write TIMING_H1 fields */
        /* If TDM mode is enabled The H Blank timing parameters should be
         * modified based on TDM Cycle format. */
        tdmRegVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcControl);
        tdmEnable = HW_GET_FIELD(tdmRegVal, DSS_DISPC_CONTROL1_TDMENABLE);
        if (tdmEnable == TRUE)
        {
            tdmCycleFormat = HW_GET_FIELD(tdmRegVal,
                                          DSS_DISPC_CONTROL1_TDMCYCLEFORMAT);

            if (tdmCycleFormat == 0x1U)
            {
                /* 2 Cycles for 1 Pixel: Multiply HBlank by 2. */
                hBlankMultFact = 2U;
                hBlankDivFact  = 1U;
            }
            else if (tdmCycleFormat == 0x2U)
            {
                /* 3 Cycles for 1 Pixel: Multiply HBlank by 3. */
                hBlankMultFact = 3U;
                hBlankDivFact  = 1U;
            }
            else if (tdmCycleFormat == 0x3U)
            {
                /* 3 Cycles for 2 Pixel: Multiply HBlank by 1.5. */
                hBlankMultFact = 3U;
                hBlankDivFact  = 2U;
            }
            else
            {
                /* Default to 1 cycle for 1 pixel: HBlank value should not be
                 *modified. */
                hBlankMultFact = 1U;
                hBlankDivFact  = 1U;
            }
        }
        else
        {
            /* TDM is disabled HBlank value should not be modified. */
            hBlankMultFact = 1U;
            hBlankDivFact  = 1U;
        }

        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.lcdTimingH);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_TIMING_H1_HBP,
            (((vpTimingParm.hBackPorch * hBlankMultFact) / hBlankDivFact) - 1U));
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_TIMING_H1_HFP,
            (((vpTimingParm.hFrontPorch * hBlankMultFact) / hBlankDivFact) - 1U));
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_TIMING_H1_HSW,
            (((vpTimingParm.hSyncLen * hBlankMultFact) / hBlankDivFact) - 1U));
        HW_WR_REG32(dispcOvlyObj->regOffset.lcdTimingH, regVal);

        /* write TIMING_V1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.lcdTimingV);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_TIMING_V1_VBP,
            vpTimingParm.vBackPorch);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_TIMING_V1_VFP,
            vpTimingParm.vFrontPorch);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_TIMING_V1_VSW,
            vpTimingParm.vSyncLen - 1U);
        HW_WR_REG32(dispcOvlyObj->regOffset.lcdTimingV, regVal);

        /* write width and height */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.panelSize);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_SIZE_LCD1_LPP,
            vpTimingParm.height - 1U);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_SIZE_LCD1_PPL,
            vpTimingParm.width - 1U);
        HW_WR_REG32(dispcOvlyObj->regOffset.panelSize, regVal);

        /* set scan format */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcConfig);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_OUTPUTMODEENABLE,
            vpTimingParm.scanFormat);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcConfig, regVal);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdSetClkDivisors
 *  \brief Configures the LCD Divisor Params.
 *
 *  This function will configures LCD and PCD divisor values for
 *  the overlays. Resultant pixel clock is as per formula
 *  DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdDivisorParm    Pointer to the LCD Divisor Param structure,
 *                             VpsHal_DssDispcLcdDivisorParam.This parameter
 * should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSetClkDivisors(
    VpsHal_Handle                         handle,
    const VpsHal_DssDispcLcdDivisorParam *lcdDivisorParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdDivisorParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if ((lcdDivisorParm->divisorLCD == 0) ||
        (lcdDivisorParm->divisorPCD == 0))
    {
        GT_0trace(VpsHalTrace, GT_ERR, "LCD/PCD value Zero is invalid\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write DIVISOR1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.lcdDivisor);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DIVISOR1_LCD,
            lcdDivisorParm->divisorLCD);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_DIVISOR1_PCD,
            lcdDivisorParm->divisorPCD);
        HW_WR_REG32(dispcOvlyObj->regOffset.lcdDivisor, regVal);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdOutputConf
 *  \brief Configures the data format and interface width of LCD Overlay,
 *
 *  This function will configure Output parameters of LCD overlay.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdOutputConf(
    VpsHal_Handle                        handle,
    const VpsHal_DssDispcLcdOutputParam *lcdOutParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdOutParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write CONTROL1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcControl);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONTROL1_TFTDATALINES,
            lcdOutParm->videoIfWidth);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcControl, regVal);

        if (lcdOutParm->dvoFormat == VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
        {
            halDispcOvlyBT656_1120Conf(
                handle,
                VPS_DCTRL_DVOFMT_BT656_EMBSYNC,
                (UInt32) TRUE);
        }
        else if (lcdOutParm->dvoFormat == VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
        {
            halDispcOvlyBT656_1120Conf(
                handle,
                VPS_DCTRL_DVOFMT_BT1120_EMBSYNC,
                (UInt32) TRUE);
        }
        else if (lcdOutParm->dvoFormat == VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC)
        {
            halDispcOvlyBT656_1120Conf(
                handle,
                VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC,
                (UInt32) FALSE);
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid DVO format \n");
            retVal = BSP_EBADARGS;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdSignalPolarityConf
 *  \brief Configures the Polarity of LCD Overlay signals(hsync,vsync,pclk,DE).
 *
 *  This function will configure Signal parameters like polarity of
 *  Pixel clock, Hsync, Vsync and active video.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSignalPolarityConf(
    VpsHal_Handle                          handle,
    VpsHal_DssDispcLcdSignalPolarityParam *lcdSignalPolParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdSignalPolParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    /* High polarity for interface is low for LCD and
     * vice versa */
    if (lcdSignalPolParm->vsPolarity == VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->vsPolarity = VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->vsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    }
    if (lcdSignalPolParm->hsPolarity == VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->hsPolarity = VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->hsPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    }
    if (lcdSignalPolParm->pixelClkPolarity == VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    }
    if (lcdSignalPolParm->dvoActVidPolarity == VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->dvoActVidPolarity = VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->dvoActVidPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    }

    if (retVal == BSP_SOK)
    {
        /* write POL_FREQ1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.polFreq);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_IEO,
            lcdSignalPolParm->dvoActVidPolarity);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_IPC,
            lcdSignalPolParm->pixelClkPolarity);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_IHS,
            lcdSignalPolParm->hsPolarity);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_IVS,
            lcdSignalPolParm->vsPolarity);
        HW_WR_REG32(dispcOvlyObj->regOffset.polFreq, regVal);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyLcdAdvSignalConf
 *  \brief Configures the LCD Overlay signal Params.
 *
 *  This function will configure Advance Signal parameters like polarity of
 *  Pixel clock, Hsync, Vsync data sampling at raising edge or falling edge
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdAdvSignalConf(
    VpsHal_Handle                         handle,
    const Vps_DssDispcLcdAdvSignalConfig *lcdSignalParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdSignalParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write POL_FREQ1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.polFreq);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_ALIGN,
            lcdSignalParm->hVAlign);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_ONOFF,
            lcdSignalParm->hVClkControl);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_RF,
            lcdSignalParm->hVClkRiseFall);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_ACBI,
            lcdSignalParm->acBI);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_POL_FREQ1_ACB,
            lcdSignalParm->acB);
        HW_WR_REG32(dispcOvlyObj->regOffset.polFreq, regVal);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyGetIRQStat
 *  \brief This function will give the details of the interrupt signals
 *  that are currently being set.
 *
 *  This function will give the details of the interrupt being set
 *
 *  \param                void
 *
 *  \return                 Returns List of interrupts being set on success
 *                             else zero.
 */
UInt64 VpsHal_dssOvlyGetIrqStat(void)
{
    UInt64 irqStatus;

    irqStatus = (UInt64) HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_IRQSTATUS);

    return (irqStatus);
}

/**
 *  VpsHal_dssOvlyClearIrq
 *  \brief This function will clear the Interrupts.
 *
 *  This function will clear the list of interrupts
 *
 *  \param                void
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyClearIrq(UInt64 irqStatus)
{
    Int32 retVal = BSP_SOK;

    HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_IRQSTATUS, (UInt32) irqStatus);

    return (retVal);
}

/**
 *  VpsHal_dssOvlyEnableIntr
 *  \brief This function will Enable the Vync Interrupt of a particular Overlay
 *
 *  This function will Enable the interrupts related to particular overlay
 *
 *  \param                ovlHalId - Overlay HAL ID
 *
 *  \param                enable - enable or disable the interrupt
 *                          (1 to enable and 0 to disable)
 *
 *  \return               Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnableIntr(UInt32 ovlHalId, UInt32 enable)
{
    Int32 retVal = BSP_SOK;

    if (ovlHalId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if ((enable != 0U) && (enable != 1U))
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid argument \n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        switch (ovlHalId)
        {
            case VPSHAL_DSS_DISPC_LCD1:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_VSYNC1_EN,
                    enable);
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_SYNCLOST1_EN,
                    enable);
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_PROGRAMMEDLINENUMBER_EN,
                    enable);
                break;

            case VPSHAL_DSS_DISPC_LCD2:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_VSYNC2_EN,
                    enable);
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_SYNCLOST2_EN,
                    enable);
                break;

            case VPSHAL_DSS_DISPC_LCD3:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_VSYNC3_EN,
                    enable);
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_SYNCLOST3_EN,
                    enable);
                break;

            case VPSHAL_DSS_DISPC_HDMI:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_EVSYNC_EVEN_EN,
                    enable);
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_SYNCLOSTTV_EN,
                    enable);
                break;

            case VPSHAL_DSS_DISPC_WBOVR:
                HW_WR_FIELD32(
                    SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
                    DSS_DISPC_IRQENABLE_FRAMEDONEWB_EN,
                    enable);
                break;

            default:
                retVal = BSP_EFAIL;
                break;
        }

        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
            DSS_DISPC_IRQENABLE_VID1BUFFERUNDERFLOW_EN,
            enable);
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
            DSS_DISPC_IRQENABLE_VID2BUFFERUNDERFLOW_EN,
            enable);
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
            DSS_DISPC_IRQENABLE_VID3BUFFERUNDERFLOW_EN,
            enable);
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
            DSS_DISPC_IRQENABLE_GFXBUFFERUNDERFLOW_EN,
            enable);
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
            DSS_DISPC_IRQENABLE_WBBUFFEROVERFLOW_EN,
            enable);
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_IRQENABLE,
            DSS_DISPC_IRQENABLE_OCPERROR_EN,
            enable);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlySetParallelMux
 *  \brief Sets the Parallel Mux for DPI1 output
 *
 *  This function will Set Parallel Mux for DPI1 Output
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetParallelMux(UInt32 ovlyId)
{
    Int32 retVal = BSP_SOK;

    if (retVal == BSP_SOK)
    {
        switch (ovlyId)
        {
            case VPSHAL_DSS_DISPC_LCD1:
                /* LCD1 select - To select primary LCD*/
                HW_WR_FIELD32(
                    SOC_DSS_FAMILY_BASE + DSS_CTRL,
                    DSS_CTRL_PARALLEL_SEL,
                    DSS_CTRL_PARALLEL_SEL_LCD1);
                break;

            case VPSHAL_DSS_DISPC_LCD2:
                /* LCD2 select - To select primary LCD*/
                HW_WR_FIELD32(
                    SOC_DSS_FAMILY_BASE + DSS_CTRL,
                    DSS_CTRL_PARALLEL_SEL,
                    DSS_CTRL_PARALLEL_SEL_LCD2);
                break;

            case VPSHAL_DSS_DISPC_LCD3:
                /* LCD3 select - To select primary LCD*/
                HW_WR_FIELD32(
                    SOC_DSS_FAMILY_BASE + DSS_CTRL,
                    DSS_CTRL_PARALLEL_SEL,
                    DSS_CTRL_PARALLEL_SEL_LCD3);
                break;

            case VPSHAL_DSS_DISPC_HDMI:
                /* HDMI select - To select primary LCD*/
                HW_WR_FIELD32(
                    SOC_DSS_FAMILY_BASE + DSS_CTRL,
                    DSS_CTRL_PARALLEL_SEL,
                    DSS_CTRL_PARALLEL_SEL_HDMI);
                break;

            default:
                GT_0trace(VpsHalTrace, GT_ERR, "Invalid Overlay ID \n");
                retVal = BSP_EBADARGS;
                break;
        }
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlyBypassTvGamma
 *  \brief Enable or bypass Tv Gamma Table
 *
 *  This function will enable/bypass TV gamma table
 *
 *  \param enable          0 - bypass, 1- enable
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnableTvGamma(UInt32 enable)
{
    Int32 retVal = BSP_SOK;

    if ((enable != 1U) && (enable != 0U))
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid arguments  \n");
        retVal = BSP_EBADARGS;
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_CONFIG1,
            DSS_DISPC_CONFIG1_GAMATABLEENABLE,
            enable);
    }

    return (retVal);
}

/**
 *  VpsHal_dssOvlySetDispcMode
 *  \brief Configures the DISPC Mode
 *
 *  This function will configure the DISPC into master/slave mode
 *
 *  \param enable          1 - master, 0 - slave
 *
 *  \return                Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetDispcMode(UInt32 dispcMode)
{
    /* Stub for Tda2xx*/
    Int32 retVal = BSP_SOK;

    return retVal;
}

/**
 *  VpsHal_dssOvlyDpiEnable
 *  \brief Enables/Disables the DPI output
 *
 *  This function will enable or disables the DPI output.
 *
 *  \param enable          TRUE - enable, FALSE - disable
 *
 *  \return                Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyDpiEnable(UInt32 dpiEnable)
{
    /* Stub for Tda2xx*/
    Int32 retVal = BSP_SOK;

    return retVal;
}

/**
 *  VpsHal_dssOvlySetLoadMode
 *  \brief Selects the Load mode for graphics pipeline
 *
 *  This function will select the load mode for graphics pipeline
 *
 *  \param loadMode    0 - Palette/Gamma Table and data are loaded every frame
 *                     1 -  Palette/Gamma Table to be loaded
 *                     2 -  Frame data only loaded every frame
 *                     3 -  Palette/Gamma Table and frame data loaded on first
 *                                 frame then switch to 0x2 (Hardware)
 *
 *  \return     Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetLoadMode(UInt32 loadMode)
{
    Int32 retVal = BSP_SOK;

    if (loadMode > 3U)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid arguments  \n");
        retVal = BSP_EBADARGS;
    }

    if (BSP_SOK == retVal)
    {
        HW_WR_FIELD32(
            SOC_DISPC_BASE + DSS_DISPC_CONFIG1,
            DSS_DISPC_CONFIG1_LOADMODE,
            loadMode);
    }

    return (retVal);
}

/**
 *  Vpshal_dssOvlySetTvRes
 *  \brief sets the resolution of the TV overlay
 *
 *  This function will set the resolution of the TV overlay
 *
 * \return Returns BSP_SOK on success else returns error value
 *
 */
Int32 Vpshal_dssOvlySetTvRes(UInt32 height, UInt32 width)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;

    regVal = HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_SIZE_TV);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_SIZE_TV_LPP,
        height - 1U);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_SIZE_TV_PPL,
        width - 1U);
    HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_SIZE_TV, regVal);

    return (retVal);
}

/**
 *  halDispcOvlyInitInstance
 *  Initialize the DISPC OVL instance by updating the register offsets
 */
static Int32 halDispcOvlyInitInstance(VpsHal_DssDispcOvlyObj *dispcOvlyObj)
{
    Int32 retVal = BSP_SOK;

    switch (dispcOvlyObj->halId)
    {
        case VPSHAL_DSS_DISPC_LCD1:
            dispcOvlyObj->regOffset.dispcControl =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONTROL1;
            dispcOvlyObj->regOffset.dispcConfig =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONFIG1;
            dispcOvlyObj->regOffset.defaultcolor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DEFAULT_COLOR0;
            dispcOvlyObj->regOffset.panelSize =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_SIZE_LCD1;
            dispcOvlyObj->regOffset.pipeAttrib[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID1_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID2_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID3_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[3] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GFX_ATTRIBUTES;
            dispcOvlyObj->regOffset.globalAlpha =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GLOBAL_ALPHA;
            dispcOvlyObj->regOffset.transColor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TRANS_COLOR0;
            dispcOvlyObj->regOffset.dataCycle1 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA1_CYCLE1;
            dispcOvlyObj->regOffset.dataCycle2 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA1_CYCLE2;
            dispcOvlyObj->regOffset.dataCycle3 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA1_CYCLE3;
            dispcOvlyObj->regOffset.polFreq =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_POL_FREQ1;
            dispcOvlyObj->regOffset.lcdTimingH =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TIMING_H1;
            dispcOvlyObj->regOffset.lcdTimingV =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TIMING_V1;
            dispcOvlyObj->regOffset.lcdDivisor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DIVISOR1;
            dispcOvlyObj->regOffset.lineStatus =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_LINE_STATUS;
            dispcOvlyObj->regOffset.cprCoeff[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR1_COEF_R;
            dispcOvlyObj->regOffset.cprCoeff[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR1_COEF_G;
            dispcOvlyObj->regOffset.cprCoeff[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR1_COEF_B;
            break;

        case VPSHAL_DSS_DISPC_LCD2:
            dispcOvlyObj->regOffset.dispcControl =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONTROL2;
            dispcOvlyObj->regOffset.dispcConfig =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONFIG2;
            dispcOvlyObj->regOffset.defaultcolor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DEFAULT_COLOR2;
            dispcOvlyObj->regOffset.panelSize =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_SIZE_LCD2;
            dispcOvlyObj->regOffset.pipeAttrib[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID1_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID2_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID3_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[3] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GFX_ATTRIBUTES;
            dispcOvlyObj->regOffset.globalAlpha =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GLOBAL_ALPHA;
            dispcOvlyObj->regOffset.transColor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TRANS_COLOR2;
            dispcOvlyObj->regOffset.dataCycle1 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA2_CYCLE1;
            dispcOvlyObj->regOffset.dataCycle2 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA2_CYCLE2;
            dispcOvlyObj->regOffset.dataCycle3 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA2_CYCLE3;
            dispcOvlyObj->regOffset.polFreq =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_POL_FREQ2;
            dispcOvlyObj->regOffset.lcdTimingH =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TIMING_H2;
            dispcOvlyObj->regOffset.lcdTimingV =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TIMING_V2;
            dispcOvlyObj->regOffset.lcdDivisor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DIVISOR2;
            dispcOvlyObj->regOffset.cprCoeff[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR2_COEF_R;
            dispcOvlyObj->regOffset.cprCoeff[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR2_COEF_G;
            dispcOvlyObj->regOffset.cprCoeff[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR2_COEF_B;
            break;

        case VPSHAL_DSS_DISPC_LCD3:
            dispcOvlyObj->regOffset.dispcControl =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONTROL3;
            dispcOvlyObj->regOffset.dispcConfig =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONFIG3;
            dispcOvlyObj->regOffset.defaultcolor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DEFAULT_COLOR3;
            dispcOvlyObj->regOffset.panelSize =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_SIZE_LCD3;
            dispcOvlyObj->regOffset.pipeAttrib[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID1_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID2_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID3_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[3] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GFX_ATTRIBUTES;
            dispcOvlyObj->regOffset.globalAlpha =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GLOBAL_ALPHA;
            dispcOvlyObj->regOffset.transColor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TRANS_COLOR3;
            dispcOvlyObj->regOffset.dataCycle1 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA3_CYCLE1;
            dispcOvlyObj->regOffset.dataCycle2 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA3_CYCLE2;
            dispcOvlyObj->regOffset.dataCycle3 =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DATA3_CYCLE3;
            dispcOvlyObj->regOffset.polFreq =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_POL_FREQ3;
            dispcOvlyObj->regOffset.lcdTimingH =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TIMING_H3;
            dispcOvlyObj->regOffset.lcdTimingV =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TIMING_V3;
            dispcOvlyObj->regOffset.lcdDivisor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DIVISOR3;
            dispcOvlyObj->regOffset.cprCoeff[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR3_COEF_R;
            dispcOvlyObj->regOffset.cprCoeff[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR3_COEF_G;
            dispcOvlyObj->regOffset.cprCoeff[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CPR3_COEF_B;
            break;

        case VPSHAL_DSS_DISPC_HDMI:
            dispcOvlyObj->regOffset.dispcControl =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONTROL1;
            dispcOvlyObj->regOffset.dispcConfig =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONFIG1;
            dispcOvlyObj->regOffset.defaultcolor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_DEFAULT_COLOR1;
            dispcOvlyObj->regOffset.panelSize =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_SIZE_TV;
            dispcOvlyObj->regOffset.pipeAttrib[0] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID1_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[1] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID2_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[2] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_VID3_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[3] =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GFX_ATTRIBUTES;
            dispcOvlyObj->regOffset.globalAlpha =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_GLOBAL_ALPHA;
            dispcOvlyObj->regOffset.transColor =
                dispcOvlyObj->dispcBaseAddr + DSS_DISPC_TRANS_COLOR1;
            break;

        default:
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
            retVal = BSP_EBADARGS;
            break;
    }

    return (retVal);
}

/**
 *  halDispcOvlyOptimizationConf
 *  optimizes the fetching of the data for a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyOptimizationConf(VpsHal_Handle handle,
                                         UInt32        ovlyOptimization)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 halId;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;
    halId        = dispcOvlyObj->halId;

    /* Optimization field for TV is present in control2 register */
    if (halId == VPSHAL_DSS_DISPC_HDMI)
    {
        HW_WR_FIELD32(
            (UInt32) dispcOvlyObj->dispcBaseAddr + DSS_DISPC_CONTROL2,
            DSS_DISPC_CONTROL2_TVOVERLAYOPTIMIZATION,
            ovlyOptimization);
    }
    else
    {
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcControl,
            DSS_DISPC_CONTROL1_OVERLAYOPTIMIZATION,
            ovlyOptimization);
    }

    return;
}

/**
 *  VpsHal_dssOvlyGetLineNum
 *  \brief Get the lineNumber of the overlay.
 *
 *  This function will give the current line number going on for an overlay
 *
 *  \param ovlyId           Valid Ovlerlay ID
 *
 *  \param lineNum         pointer to linenumber variable
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetLineNum(UInt32 ovlyId, UInt32 *lineNum)
{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != lineNum);

    if (ovlyId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Ovl Id \n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* Currently this register is only available for LCD1 instance*/
        if (ovlyId == VPSHAL_DSS_DISPC_LCD1)
        {
            *lineNum = HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_LINE_STATUS);
        }
        else
        {
            /* not supported for other LCD's. so returning max value so
             * that
             * low latency will not be supported(i.e push mechanism will
             * not be applicable)*/
            *lineNum = 0x7FFU;
        }
    }

    return (retVal);
}

/**
 *  halDispcOvlyAlphaBlenderConf
 *  Configures the alpha Blender of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here. TODO - This is deprected check if we need this.
 */
static void halDispcOvlyAlphaBlenderConf(
    VpsHal_Handle handle,
    UInt32        alphaBlenderEnable)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 halId;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;
    halId        = dispcOvlyObj->halId;

    if (halId == VPSHAL_DSS_DISPC_HDMI)
    {
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcConfig,
            DSS_DISPC_CONFIG1_TVALPHABLENDERENABLE,
            alphaBlenderEnable);
    }
    /* AlphaEnable Field is not present for other overlays */
    else if (halId == VPSHAL_DSS_DISPC_LCD1)
    {
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcConfig,
            DSS_DISPC_CONFIG1_LCDALPHABLENDERENABLE,
            alphaBlenderEnable);
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_INFO,
                  "Not applicable for this instance\n");
    }

    return;
}

/**
 *  halDispcOvlySetBgColor
 *  Configures the background color of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlySetBgColor(VpsHal_Handle handle,
                                   UInt32        bgColor)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.defaultcolor,
        DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR,
        bgColor);

    return;
}

/**
 *  halDispcOvlyPanelSizeConf
 *  Configures the delta lines for a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPanelDeltaLinesConf(
    VpsHal_Handle handle,
    UInt32        deltaLinesPerPanel)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.panelSize,
        DSS_DISPC_SIZE_LCD1_DELTA_LPP,
        deltaLinesPerPanel);

    return;
}

/**
 *  halDispcOvlyPanelSetTransColorKey
 *  Configures the transcolorkey of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPanelSetTransColorKey(
    VpsHal_Handle handle,
    UInt32        transColorKey)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.transColor,
        DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY,
        transColorKey);

    return;
}

/**
 *  halDispcOvlyPanelColorKeyConf
 *  Configures the colorkey of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPanelColorKeyConf(VpsHal_Handle handle,
                                          UInt32        colorKeyEnable,
                                          UInt32        colorKeySel)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 halId;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;
    halId        = dispcOvlyObj->halId;

    if (halId == VPSHAL_DSS_DISPC_HDMI)
    {
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcConfig,
            DSS_DISPC_CONFIG1_TCKTVENABLE,
            colorKeyEnable);
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcConfig,
            DSS_DISPC_CONFIG1_TCKTVSELECTION,
            colorKeySel);
    }
    else
    {
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcConfig,
            DSS_DISPC_CONFIG1_TCKLCDENABLE,
            colorKeyEnable);
        HW_WR_FIELD32(
            dispcOvlyObj->regOffset.dispcConfig,
            DSS_DISPC_CONFIG1_TCKLCDSELECTION,
            colorKeySel);
    }

    return;
}

/**
 *  halDispcOvlyPipeSetChannelOut
 *  Configures the pipeline to connect to a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeSetChannelOut(VpsHal_Handle handle,
                                          UInt32        pipe)
{
    UInt32 channelOut = 0, channelout2 = 0;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    halDispcOvlyGetChannelOutVal(
        dispcOvlyObj->halId, &channelOut, &channelout2);
    if (VPS_DSS_DISPC_PIPE_GFX1 == pipe)
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT2,
            channelout2);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_GFX_ATTRIBUTES_CHANNELOUT,
            channelOut);
        HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);
    }
    else
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT2,
            channelout2);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_VID1_ATTRIBUTES_CHANNELOUT,
            channelOut);
        HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);
    }

    return;
}

/**
 *  halDispcOvlyGetChannelOutVal
 *  Returns the channel out value required for a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyGetChannelOutVal(UInt32  halId,
                                         UInt32 *chlout,
                                         UInt32 *chlout2)
{
    if (halId == VPSHAL_DSS_DISPC_HDMI)
    {
        *chlout = 1;
    }
    else
    {
        *chlout = 0x0;
        if (halId == VPSHAL_DSS_DISPC_LCD1)
        {
            *chlout2 = 0x0;
        }
        if (halId == VPSHAL_DSS_DISPC_LCD2)
        {
            *chlout2 = 0x1;
        }
        if (halId == VPSHAL_DSS_DISPC_LCD3)
        {
            *chlout2 = 0x2;
        }
    }

    return;
}

/**
 *  halDispcOvlyPipeSetPreMulAlpha
 *  Sets the Premultiply alpha value for a particular pipeline
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeSetPreMulAlpha(
    VpsHal_Handle handle,
    UInt32        pipe,
    UInt32        preMultiplyAlpha)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.pipeAttrib[pipe],
        DSS_DISPC_VID1_ATTRIBUTES_PREMULTIPHYALPHA,
        preMultiplyAlpha);

    return;
}

/**
 *  halDispcOvlyPipeSetGlobalAlpha
 *  Sets the Global Alpha value for a particular pipeline
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeSetGlobalAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        globalAlpha)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    switch (pipe)
    {
        case VPS_DSS_DISPC_PIPE_VID1:
            HW_WR_FIELD32(
                dispcOvlyObj->regOffset.globalAlpha,
                DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA,
                globalAlpha);
            break;

        case VPS_DSS_DISPC_PIPE_VID2:
            HW_WR_FIELD32(
                dispcOvlyObj->regOffset.globalAlpha,
                DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA,
                globalAlpha);
            break;

        case VPS_DSS_DISPC_PIPE_VID3:
            HW_WR_FIELD32(
                dispcOvlyObj->regOffset.globalAlpha,
                DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA,
                globalAlpha);
            break;

        case VPS_DSS_DISPC_PIPE_GFX1:
            HW_WR_FIELD32(
                dispcOvlyObj->regOffset.globalAlpha,
                DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA,
                globalAlpha);
            break;

        default:
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
            break;
    }

    return;
}

/**
 *  halDispcOvlyPipeConfZorder
 *  Sets the Z-Order of a particular pipeline connected to this overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeConfZorder(VpsHal_Handle handle,
                                       UInt32        pipe,
                                       UInt32        zorder,
                                       UInt32        zorderEnable)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_VID1_ATTRIBUTES_ZORDER,
        zorder);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_VID1_ATTRIBUTES_ZORDERENABLE,
        zorderEnable);
    HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);

    return;
}

/**
 *  halDssVidConfCprCoeff
 *  Configures the coefficients for color phase rotation
 */
static void halDispcConfCprCoeff(VpsHal_Handle handle)
{
    /* Coefficients for BT601-5 RGB to YUV conversion */
    static const VpsHal_DssDispcCprCoeff cprCoeff =
    {77, 150, 29, -44, -87, 131, 131, -110, -21};
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[0],
        DSS_DISPC_CPR1_COEF_R_RB,
        cprCoeff.rb);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[0],
        DSS_DISPC_CPR1_COEF_R_RG,
        cprCoeff.rg);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[0],
        DSS_DISPC_CPR1_COEF_R_RR,
        cprCoeff.rr);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[1],
        DSS_DISPC_CPR1_COEF_G_GB,
        cprCoeff.gb);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[1],
        DSS_DISPC_CPR1_COEF_G_GG,
        cprCoeff.gg);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[1],
        DSS_DISPC_CPR1_COEF_G_GR,
        cprCoeff.gr);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[2],
        DSS_DISPC_CPR1_COEF_B_BB,
        cprCoeff.bb);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[2],
        DSS_DISPC_CPR1_COEF_B_BG,
        cprCoeff.bg);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.cprCoeff[2],
        DSS_DISPC_CPR1_COEF_B_BR,
        cprCoeff.br);

    return;
}

/**
 *  haldssOvlyBT656_1120Conf
 *  \brief Configures the BT656_1120
 *
 *  This function will configure BT656 or 1120  bit and CPR coefficients
 *  when BT656/1120 is enabled
 *
 *  \param handle           Valid handle returned by haldssOvlyBT656_1120Conf
 *                          function
 *  \param  dvoFormat   Format  BT656/1120
 *  \param  enable   Enable or disable BT656/1120
 *  \return                 Returns BSP_SOK on success else returns error value
 */
static Int32 halDispcOvlyBT656_1120Conf(
    VpsHal_Handle handle,
    UInt32        dvoFormat,
    UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_HDMI)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not supported for TV overlay\n");
        retVal = BSP_EBADARGS;
    }

    if ((retVal == BSP_SOK) && (enable == TRUE))
    {
        halDispcConfCprCoeff(handle);

        if (dvoFormat == VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
        {
            regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcConfig);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_BT656ENABLE,
                1U);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_BT1120ENABLE,
                0U);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_CPR,
                0U);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_COLORCONVENABLE,
                1U);
            HW_WR_REG32(dispcOvlyObj->regOffset.dispcConfig, regVal);
        }
        else if (dvoFormat == VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
        {
            regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcConfig);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_BT656ENABLE,
                0U);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_BT1120ENABLE,
                1U);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_CPR,
                0U);
            HW_SET_FIELD32(
                regVal,
                DSS_DISPC_CONFIG1_COLORCONVENABLE,
                1U);
            HW_WR_REG32(dispcOvlyObj->regOffset.dispcConfig, regVal);
        }
        else
        {
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else if ((retVal == BSP_SOK) && (enable == FALSE))
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcConfig);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_BT656ENABLE,
            0U);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_BT1120ENABLE,
            0U);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_CPR,
            0U);
        HW_SET_FIELD32(
            regVal,
            DSS_DISPC_CONFIG1_COLORCONVENABLE,
            0U);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcConfig, regVal);
    }
    else
    {
        retVal = BSP_EINVALID_PARAMS;
    }

    return (retVal);
}

/**
 *  halDispcFclkDivSet
 *  Set the divider value such that fucntional clock of DSS will be max
 */
static void halDispcFclkDivSet(void)
{
    /* Setting the divider value to 1*/
    HW_WR_FIELD32(
        SOC_DISPC_BASE + DSS_DISPC_DIVISOR,
        DSS_DISPC_DIVISOR_LCD,
        1U);

    /* Enabled to use above set divider value*/
    HW_WR_FIELD32(
        SOC_DISPC_BASE + DSS_DISPC_DIVISOR,
        DSS_DISPC_DIVISOR_ENABLE,
        1U);

    return;
}

/**
 *  halDispcSetDefIntfWidth
 *  Set the DPI interface width to 24bit, hardware default value is 12 bit.
 */
static void halDispcSetDefIntfWidth(void)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_CONTROL1);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_CONTROL1_TFTDATALINES,
        DSS_DISPC_CONTROL1_TFTDATALINES_OALSB24B);
    HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_CONTROL1, regVal);

    regVal = HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_CONTROL2);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_CONTROL2_TFTDATALINES,
        DSS_DISPC_CONTROL2_TFTDATALINES_OALSB24B);
    HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_CONTROL2, regVal);

    regVal = HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_CONTROL3);
    HW_SET_FIELD32(
        regVal,
        DSS_DISPC_CONTROL3_TFTDATALINES,
        DSS_DISPC_CONTROL3_TFTDATALINES_OALSB24B);
    HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_CONTROL3, regVal);
}

/**
 *  halDispcReset
 *  Resets the DISPC module
 */
static void halDispcReset(void)
{
    UInt32 dispcStatus;

    /* No Standby*/
    HW_WR_FIELD32(
        SOC_DISPC_BASE + DSS_DISPC_SYSCONFIG,
        DSS_DISPC_SYSCONFIG_MIDLEMODE,
        1U);

    /* Disable */
    HW_WR_FIELD32(
        SOC_DISPC_BASE + DSS_DISPC_CONTROL1,
        DSS_DISPC_CONTROL1_LCDENABLE,
        0U);

    /* Disable */
    HW_WR_FIELD32(
        SOC_DISPC_BASE + DSS_DISPC_CONTROL2,
        DSS_DISPC_CONTROL2_LCDENABLE,
        0U);

    /* Soft reset*/
    HW_WR_FIELD32(
        SOC_DISPC_BASE + DSS_DISPC_SYSCONFIG,
        DSS_DISPC_SYSCONFIG_SOFTRESET,
        1U);

    dispcStatus = HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_SYSSTATUS);

    /* TODO For now comment it, we need to check the status before
     *starting */
    /* while(HW_RD_REG32(SOC_DISPC_BASE + DSS_DISPC_SYSSTATUS) != 1); */
    if (dispcStatus != 1U)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "DSS Still in reset");
    }

    return;
}

static void halDispcDisableMstandbyEnhancement(void)
{
    HW_WR_REG32(SOC_DISPC_BASE + DSS_DISPC_DISABLE_MSTANDBY_ENHANCEMENT, 1U);
}

