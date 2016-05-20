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

#include <app_dssConfigure.h>

/**
 * Open Capture Handle
 */
VpsDrv_DispInstObj *App_dsscoreOpen(UInt32 dssInstId)
{
    VpsDrv_DispInstObj   *pObj = NULL;
    VpsCore_OpenPrms      openParams;
    VpsCore_DssOpenParams dssOpenParams;

    openParams.reqFrmCb  = (VpsCore_ReqFrameCb) App_DssqueBufs;
    openParams.frmDoneCb = (VpsCore_FrameDoneCb) App_DssdeQueBufs;

    pObj = VpsDrv_dssOpen(dssInstId, &openParams, &dssOpenParams);

    return pObj;
}

Int32 App_dsscoreClose(VpsDrv_DispInstObj *pObj)
{
    return VpsDrv_dssClose(pObj);
}

Int32 App_dsscoreStart(VpsDrv_DispInstObj *pObj)
{
    return VpsDrv_dssStart(pObj);
}

Int32 App_dsscoreStop(VpsDrv_DispInstObj *pObj)
{
    return VpsDrv_dssStop(pObj);
}

Int32 App_dssconfigure(VpsDrv_DispInstObj *pObj)
{
    VpsDrv_DispDssParams  dssPrms;
    Vps_DssDispcVidConfig videoCfg;
    UInt32 dataFormat = FVID2_DF_YUV422I_YUYV;

    dssPrms.inFmt.dataFormat = dataFormat;
    dssPrms.inFmt.width      = 720U;
    dssPrms.inFmt.height     = 480U;

    if (Fvid2_isDataFmtSemiPlanar(dataFormat))
    {
        dssPrms.inFmt.pitch[FVID2_YUV_SP_Y_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[FVID2_YUV_SP_CBCR_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtYuv422I(dataFormat))
    {
        dssPrms.inFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width * 2U, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtRgb16bit(dataFormat))
    {
        dssPrms.inFmt.pitch[FVID2_YUV_INT_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width * 2U, VPS_BUFFER_ALIGNMENT);
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtRgb24bit(dataFormat))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        dssPrms.inFmt.pitch[FVID2_RGB_ADDR_IDX] =
            VpsUtils_align(dssPrms.inFmt.width * 3U,
                           (VPS_BUFFER_ALIGNMENT * 3U));
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else if (Fvid2_isDataFmtRgb32bit(dataFormat))
    {
        /* Align the pitch to BPP boundary as well since the pitch
         * aligined to VPS_BUFFER_ALIGNMENT may not be multiple of 3
         * bytes (1 pixel) */
        dssPrms.inFmt.pitch[FVID2_RGB_ADDR_IDX] = VpsUtils_align(
            dssPrms.inFmt.width * 4U,
            (
                VPS_BUFFER_ALIGNMENT));;
        dssPrms.inFmt.pitch[1U] = 0;
        dssPrms.inFmt.pitch[2U] = 0;
    }
    else
    {
        /* If the condition is not matched with anything, do nothhing
         * TODO: Raise an error condition that input does not match any format*/
        printf("Error configuring DSS, data format not supporter");
    }
    dssPrms.inFmt.chNum           = 0U;
    dssPrms.inFmt.fieldMerged[0U] = FALSE;
    dssPrms.inFmt.fieldMerged[1U] = FALSE;
    dssPrms.inFmt.fieldMerged[2U] = FALSE;
    dssPrms.inFmt.scanFormat      = FVID2_SF_PROGRESSIVE;
    dssPrms.inFmt.bpp      = FVID2_BPP_BITS16;
    dssPrms.inFmt.reserved = NULL;
    dssPrms.tarWidth       = 720U;
    dssPrms.tarHeight      = 480U;
    dssPrms.posX           = 40U;
    dssPrms.posY           = 0;

    videoCfg.pipeCfg.repliEnable      = FALSE;
    videoCfg.pipeCfg.scEnable         = FALSE;
    videoCfg.pipeCfg.cscFullRngEnable = VPS_DSS_DISPC_CSC_FULL;
    videoCfg.pipeCfg.chromaSampling   = 0U;
    videoCfg.advDmaCfg = NULL;
    videoCfg.vc1Cfg    = NULL;

    dssPrms.vidCfg = &videoCfg;

    return VpsDrv_dssSetParams(pObj, &dssPrms);
}

