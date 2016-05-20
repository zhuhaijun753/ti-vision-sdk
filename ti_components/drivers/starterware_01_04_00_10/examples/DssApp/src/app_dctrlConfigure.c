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
#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>

#include <app_dctrlConfigure.h>
#include "pmhal_prcm.h"
#include "pmlib_videopll.h"

static Int32 DispApp_configureVideoPllAndClkSrc(UInt32 pixelClk);

/**
 * Open Dctrl Handle
 */
VpsDrv_DctrlInstObj *App_dctrlcoreOpen(void)
{
    VpsDrv_DctrlInstObj *pObj = NULL;

    pObj = VpsDrv_dctrlOpen();

    return pObj;
}

Int32 App_dctrlcoreClose(VpsDrv_DctrlInstObj *pObj)
{
    return VpsDrv_dctrlClose(pObj);
}

Int32 App_configureDctrl(VpsDrv_DctrlInstObj *pObj)
{
    Vps_DctrlConfig             dctrlCfg;
    Vps_DssDispcOvlyPanelConfig panelCfg;
    Vps_DctrlVencDivisorInfo    vencDivisors;
    Int32 retVal, idx = 0;
    UInt32 pixelClock;

    dctrlCfg.useCase = VPS_DCTRL_USERSETTINGS;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID1_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = VPS_DCTRL_DSS_LCD1_BLENDER;
    idx++;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID2_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = VPS_DCTRL_DSS_LCD1_BLENDER;
    idx++;

#if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD)
    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_VID3_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = VPS_DCTRL_DSS_LCD1_BLENDER;
    idx++;
#endif

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_GFX1_INPUT_PATH;
    dctrlCfg.edgeInfo[idx].endNode   = VPS_DCTRL_DSS_LCD1_BLENDER;
    idx++;

    dctrlCfg.edgeInfo[idx].startNode = VPS_DCTRL_DSS_LCD1_BLENDER;
    dctrlCfg.edgeInfo[idx].endNode   = VPS_DCTRL_DSS_DPI1_OUTPUT;
    idx++;

    dctrlCfg.numEdges = (UInt32) idx;

    dctrlCfg.vencInfo.numVencs = (UInt32) 1U;
    dctrlCfg.vencInfo.modeInfo[0U].vencId = VPS_DCTRL_DSS_VENC_LCD1;

    /* Configure custom timings */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.standard = FVID2_STD_CUSTOM;

#if defined (TDA2XX_BUILD) || defined (OMAP5X_FAMILY_BUILD)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 800;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 480;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per LCD connected(Three 7 LCD)
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 29232U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 40U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 40U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 48U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 13U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 29U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 3U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif

#if defined (TDA3XX_FAMILY_BUILD) || defined (TDA2EX_BUILD)
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.width      = 1280;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.height     = 800;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.scanFormat = FVID2_SF_PROGRESSIVE;
    /*
     * Timing is as per LCD connected(10 Inch LG)
     */
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock  = (UInt32) 74500U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.fps         = (UInt32) 60U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hFrontPorch = (UInt32) 80U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hBackPorch  = (UInt32) 62U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.hSyncLen    = (UInt32) 48U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vFrontPorch = (UInt32) 12U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vBackPorch  = (UInt32) 35U;
    dctrlCfg.vencInfo.modeInfo[0U].mInfo.vSyncLen    = (UInt32) 6U;

    dctrlCfg.vencInfo.tiedVencs = (UInt32) 0U;
#endif
    retVal = vpsDrv_DctrlSetConfig(pObj, &dctrlCfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("DCTRL Set Config Failed!!!\n");
    }

    panelCfg.vencId = VPS_DCTRL_DSS_VENC_LCD1;
    panelCfg.alphaBlenderEnable = (UInt32) 0;
    panelCfg.backGroundColor    = 0x101010;
    panelCfg.colorKeyEnable     = 1;
    /* Source transparency color key selected */
    panelCfg.colorKeySel        = VPS_DSS_DISPC_TRANS_COLOR_KEY_SRC;
    panelCfg.deltaLinesPerPanel = (UInt32) 0;
    panelCfg.transColorKey      = 0x00;

    vpsDrv_DctrlSetOvlyParams(pObj, &panelCfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf(": DCTRL Set Config Failed!!!\n");
    }

    /* Setting LCD and PCD values to 1 */
    vencDivisors.vencId     = VPS_DCTRL_DSS_VENC_LCD1;
    vencDivisors.divisorLCD = 1;
    vencDivisors.divisorPCD = 1;

#if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD)
    /* Using Video1 Pll as clock source for LCD1 Venc. If frequency is
     * 29.232 MHz, video PLL can't lock. Hence set Video1Pll programmed to
     * output 29.232 * 4 MHz and set PCD as 4. */
    if (29232U == dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock)
    {
        vencDivisors.divisorPCD = 4U;
    }
#endif
    vpsDrv_DctrlSetVencDivisor(pObj, &vencDivisors);
    if (retVal != BSP_SOK)
    {
        Bsp_printf("DCTRL Set Venc Divisors Failed!!!\n");
    }

    pixelClock = dctrlCfg.vencInfo.modeInfo[0U].mInfo.pixelClock *
                    vencDivisors.divisorPCD;
    DispApp_configureVideoPllAndClkSrc(pixelClock);

    return retVal;
}

Int32 App_configureDctrlPipe(VpsDrv_DctrlInstObj *pObj)
{
    Vps_DssDispcOvlyPipeConfig ovlpipecfg;
    Int32 retVal = BSP_SOK;

    ovlpipecfg.pipeLine    = VPS_DSS_DISPC_PIPE_VID1;
    ovlpipecfg.globalAlpha = 0xFF;
    /* Z-order is in order GFX - 3, VID3 -2 ,VID2 - 1 and VID1 - 0 */
    ovlpipecfg.zorder = VPS_DSS_DISPC_PIPE_VID1;

    ovlpipecfg.zorderEnable     = 1;
    ovlpipecfg.preMultiplyAlpha = 0;

    retVal = vpsDrv_DctrlSetPipelineParams(pObj, &ovlpipecfg);

    if (retVal != BSP_SOK)
    {
        Bsp_printf(": DCTRL Set Config IOCTL Failed!!!\n");
    }
    return retVal;
}

static Int32 DispApp_configureVideoPllAndClkSrc(UInt32 pixelClk)
{
    Int32  retVal = BSP_EFAIL;
    pmhalPrcmNodeId_t videopllId;
    UInt32 timeDelay = 0xFFFFFFFFU;

#if defined (TDA3XX_FAMILY_BUILD)
    videopllId = PMHAL_PRCM_DPLL_EVE_VID_DSP;
#else
    videopllId = PMHAL_PRCM_VIDEOPLL_VIDEO1;
#endif
    retVal = PMLIBVideopllSetFreq(videopllId, pixelClk, timeDelay);
    if (retVal != FVID2_SOK)
    {
        Bsp_printf("Configuring Pll Failed!!!\n");
    }

#if defined (TDA2XX_FAMILY_BUILD)
    if (FVID2_SOK == retVal)
    {
        retVal = PMLIBVideopllSetVencClkSrc(
            PMLIB_VIDEOPLL_VENC_LCD1,
            PMLIB_VIDEOPLL_CLKSRC_DPLL_VIDEO1_CLKOUT1);
    }
#endif

    return retVal;
}
