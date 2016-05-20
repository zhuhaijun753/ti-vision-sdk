/**
 *  \file vpscore_iscommonpriv.c
 *
 *  \brief This file implements certain common features/functionality
 *         of the iss drivers like GLBCE startup sequence etc.
 *
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 */
/*
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include <fvid2/fvid2_dataTypes.h>

#include <isscore/vpscore_isscommoncfg.h>
#include <hal/vpshal_iss.h>
#include <hal/vpshal_isscal.h>

#include <isscore/src/vpscore_isscommon.h>

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VCORE_ISP_TIMEOUT                   (1000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Connects/disconnects Bys output to GLBCE */
static int32_t vcoreIssSetGlbceVmux(
    uint32_t calInstId,
    uint32_t flag);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t vcore_issGlbceDoInit(
    isshalCalInstId_t    calInstId,
    VpsHal_Handle        calHalHandle,
    isshalCalCfg_t      *calCfg,
    isshalCalDmaVcCfg_t *calDmaCfg)
{
    int32_t               status = FVID2_SOK;
    volatile uint32_t     timeout;
    isshalCalBufferAddr_t calBuff;

    /* Check for Null value */
    GT_assert(VpsIssCoreTrace, (NULL != calHalHandle));
    GT_assert(VpsIssCoreTrace, (NULL != calCfg));
    GT_assert(VpsIssCoreTrace, (NULL != calDmaCfg));

    /* Do Startup Sequence */
    /* Steps
     *  1, Connect CAL to GLBCE in GLBCE_SW
     *  2, Disable GLBCE at the VMUX
     *  3, Configure CAL for Read DMA
     *  4, Start the CAL and wait for Bysout EOF Intr
     *  5, Configure GLBCE mux
     *  6, Wait for the filter done interrupt
     */

    /* 1, Connect CAL to GLBCE in GLBCE_SW */
    VpsHal_issSetGlbceSwitch(
        ISSHAL_GLBCE_SWITCH_GLBCE,
        ISSHAL_GLBCE_SWITCH_CAL);

    /* 2, Disable GLBCE at the VMUX */
    vcoreIssSetGlbceVmux(calInstId, (uint32_t) FALSE);

    calCfg->numCPortId  = 2U;
    calCfg->cportId[0U] = 0x0U;
    calCfg->cportId[1U] = 0x1U;

    calDmaCfg->isRdDmaCfgValid[0U] = (uint32_t) TRUE;

    calDmaCfg->rdDmaCfg[0U].enable       = (uint32_t) TRUE;
    calDmaCfg->rdDmaCfg[0U].pixClock     = 65536U; /*Setting the max pix
                                                   *clock*/
    calDmaCfg->rdDmaCfg[0U].bwLimit      = 0x9U;  /*Setting it to minimum
                                                   *value*/
    calDmaCfg->rdDmaCfg[0U].ocpTagCnt    = 0xFU;
    calDmaCfg->rdDmaCfg[0U].bysOutLeWait = (uint32_t) TRUE;
    calDmaCfg->rdDmaCfg[0U].ySkipMode    = 0U; /* No Line Skip */

    calDmaCfg->rdDmaCfg[0U].format.width      = 0x8U;
    calDmaCfg->rdDmaCfg[0U].format.height     = 0x1U;
    calDmaCfg->rdDmaCfg[0U].format.dataFormat = FVID2_DF_BAYER_GRBG;
    calDmaCfg->rdDmaCfg[0U].format.bpp        = FVID2_BPP_BITS12;
    calDmaCfg->rdDmaCfg[0U].format.pitch[0U]  =
        calDmaCfg->rdDmaCfg[0U].format.width*2U;
    calDmaCfg->rdDmaCfg[0U].format.pitch[1U] =
        calDmaCfg->rdDmaCfg[0U].format.width*2U;
    calDmaCfg->rdDmaCfg[0U].format.pitch[2U] =
        calDmaCfg->rdDmaCfg[0U].format.width*2U;

    /* Set the Video Port configuration */
    calCfg->isVportCfgValid[0U] = (uint32_t) TRUE;
    calCfg->vportCfg[0U].enable = (uint32_t) FALSE;

    /* Set the BysOutConfig configuration */
    calCfg->isBysOutCfgValid[0U] = (uint32_t) TRUE;
    calCfg->bysOutCfg[0U].enable = (uint32_t) TRUE;
    calCfg->bysOutCfg[0U].pixClock           = 16384U;
    calCfg->bysOutCfg[0U].yBlk               = 0x00U;
    calCfg->bysOutCfg[0U].xBlk               = 0x00U;
    calCfg->bysOutCfg[0U].copyStreamToEncode = (uint32_t) FALSE;
    calCfg->bysOutCfg[0U].freeRun            = (uint32_t) TRUE;

    calCfg->isBysInCfgValid[1U] = (uint32_t) TRUE;
    calCfg->bysInEnable[1U]     = (uint32_t) TRUE;

    calCfg->pDmaVcCfg = calDmaCfg;

    status = VpsHal_isscalControl(
        calHalHandle,
        VPS_HAL_ISS_IOCTL_CAL_SETCFG,
        calCfg,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    /* Program the buffer addresses first */
    calBuff.numBuff      = 1U;
    calBuff.cPortId[0U]  = 0U;
    calBuff.wrDmaCtx[0U] = (uint32_t) FALSE;
    calBuff.buffAddr[0U] = VCORE_ISS_READ_ADDR_GBLCE_STARTUP_SEQ;
    calBuff.pitch[0U]    = 1280U*2U;

    status = VpsHal_isscalControl(
        calHalHandle,
        VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS,
        &calBuff,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    status = VpsHal_isscalRdDmaStart(
        calHalHandle,
        ISSHAL_ISS_PROC_MODE_ONE_SHOT,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    /* Wait for the BysOut End of Frame Intr */
    timeout = VCORE_ISP_TIMEOUT;
    if(VPS_HAL_ISS_CAL_INST_A == calInstId)
    {
        do
        {
            if(((*(volatile uint32_t *) 0x52012020U) & 0x8U) != 0U)
            {
                break;
            }
            timeout--;
        } while(timeout > 0U);

        if((0U == timeout) &&
           (((*(volatile uint32_t *) 0x52012020U) & 0x8U) == 0U))
        {
            /* TODO: How To Report this error */
        }
    }
    else
    {
        do
        {
            if(((*(volatile uint32_t *) 0x52013020U) & 0x8U) != 0U)
            {
                break;
            }
            timeout--;
        } while(timeout > 0U);

        if((0U == timeout) &&
           (((*(volatile uint32_t *) 0x52013020U) & 0x8U) == 0U))
        {
            /* TODO: How To Report this error */
        }
    }

    vcoreIssSetGlbceVmux(calInstId, (uint32_t) TRUE);

    /* Wait for the Filter Done Interrupt */
    timeout = VCORE_ISP_TIMEOUT;
    do
    {
        if(((*(volatile uint32_t *) 0x520400B8U) & 0x10000U) != 0U)
        {
            break;
        }
        timeout--;
    } while(timeout > 0U);

    if((0U == timeout) &&
       (((*(volatile uint32_t *) 0x520400B8U) & 0x10000U) == 0U))
    {
        /* TODO: How To Report this error */
    }

    /* Disabled BysOut and Bysin ports */
    calCfg->numCPortId  = 1U;
    calCfg->cportId[0U] = 0x0U;

    calCfg->isBysOutCfgValid[0U]   = (uint32_t) TRUE;
    calCfg->bysOutCfg[0U].enable   = (uint32_t) FALSE;
    calCfg->bysOutCfg[0U].pixClock = 0U;
    calCfg->isBysInCfgValid[0U]    = (uint32_t) TRUE;
    calCfg->bysInEnable[0U]        = (uint32_t) FALSE;

    status = VpsHal_isscalControl(
        calHalHandle,
        VPS_HAL_ISS_IOCTL_CAL_SETCFG,
        calCfg,
        NULL);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* Connects/disconnects Bys output to GLBCE */
static int32_t vcoreIssSetGlbceVmux(
    uint32_t calInstId,
    uint32_t flag)
{
    int32_t status = FVID2_SOK;
    isshalVMuxSrcPorts_t  vmuxSrc;
    isshalVMuxSinkPorts_t vmuxSink;

    if(VPS_HAL_ISS_CAL_INST_A == calInstId)
    {
        vmuxSrc = SRC_PORT_CAL_A_BYS_OUT;
    }
    else
    {
        vmuxSrc = SRC_PORT_CAL_B_BYS_OUT;
    }
    vmuxSink = SINK_PORT_GLBCE_IN;

    /* Gate the clock first */
    status = VpsHal_issvmuxClkCtrl(
        vmuxSrc,
        vmuxSink,
        (uint32_t) FALSE);
    GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));

    if(FVID2_SOK == status)
    {
        if((uint32_t) FALSE == flag)
        {
            status = VpsHal_issvmuxSetPath(
                vmuxSrc,
                vmuxSink,
                (uint32_t) FALSE);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        }
        else
        {
            /* Setup the path */
            status = VpsHal_issvmuxSetPath(
                vmuxSrc,
                vmuxSink,
                (uint32_t) TRUE);
            GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
        }
    }

    if(FVID2_SOK == status)
    {
        /* Enable the clock */
        status = VpsHal_issvmuxClkCtrl(
            vmuxSrc,
            vmuxSink,
            (uint32_t) TRUE);
        GT_assert(VpsIssCoreTrace, (FVID2_SOK == status));
    }

    return (status);
}

