/**
 *  \file isshal_glbce_dummy.c
 *
 *  \brief File containing the ISS GLBCE HAL init, deinit and other common
 *  functions.
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
#include <common/bsp_types.h>
#include <fvid2/fvid2_dataTypes.h>
#include <hal/vpshal.h>
#include <hal/vpshal_iss.h>
#include <hal/vpshal_issglbce.h>

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

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issglbceInit(
    uint32_t                       numInst,
    const isshalglbceInstParams_t *instPrms,
    Ptr                            arg)
{
    return (FVID2_SOK);
}

int32_t VpsHal_issglbceDeInit(Ptr arg)
{
    return (FVID2_SOK);
}

VpsHal_Handle VpsHal_issglbceOpen(const isshalOpenParams_t *openPrms,
                                  Ptr                       arg)
{
    return (NULL);
}

int32_t VpsHal_issglbceClose(VpsHal_Handle handle,
                             Ptr           arg)
{
    return (FVID2_ENO_DEVICE);
}

int32_t VpsHal_issglbceSetConfig(
    VpsHal_Handle              handle,
    const isshalglbceConfig_t *cfg,
    Ptr                        arg)
{
    return (FVID2_ENO_DEVICE);
}

int32_t VpsHal_issglbceGetConfig(
    VpsHal_Handle        handle,
    isshalglbceConfig_t *config)
{
    return (FVID2_ENO_DEVICE);
}

int32_t VpsHal_issglbceControl(
    VpsHal_Handle handle,
    uint32_t      cmd,
    Ptr           cmdArgs,
    Ptr           arg)
{
    return (FVID2_ENO_DEVICE);
}

int32_t VpsHal_issglbceStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    return (FVID2_ENO_DEVICE);
}

int32_t VpsHal_issglbceStop(
    VpsHal_Handle handle,
    Ptr           arg)
{
    return (FVID2_ENO_DEVICE);
}

