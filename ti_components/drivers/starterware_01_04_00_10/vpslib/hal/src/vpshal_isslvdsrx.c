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

/**
 *  \file isshal_isslvdsrx.c
 *
 *  \brief File containing the ISS LVDSRX HAL init, deinit and other common
 *  functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <hw/hw_iss_lvdsrx.h>
#include <hw/hw_types.h>
#include <fvid2/fvid2_dataTypes.h>
#include <hal/vpshal.h>
#include <hal/vpshal_iss.h>
#include <hal/vpshal_isslvdsrx.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define LVDSRX_CAMERA_CFG_DIFF      (LVDSRX_CAM2_CFG - LVDSRX_CAM1_CFG)

#define LVDSRX_CAM_CFG              (0x0U)
#define LVDSRX_CAM_FRMSIZE          (0x4U)
#define LVDSRX_CAM_MAXWIDTH         (0x8U)
#define LVDSRX_CAM_SYNCSOF          (0xCU)
#define LVDSRX_CAM_SYNCEOF          (0x10U)
#define LVDSRX_CAM_SYNCSOL          (0x14U)
#define LVDSRX_CAM_SYNCEOL          (0x18U)
#define LVDSRX_CAM_SYNCSOV          (0x1CU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshallvdsrxInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
    uint32_t maxPhys;
    /**< Maximum number of PHY supported */
    uint32_t maxLanesPerPhy;
    /**< Maximum number of lanes supported per phy */
} isshallvdsrxInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Void LvdsrxReset(VpsHal_Handle handle);
static inline uint32_t LvdsRxCameraOffset(uint32_t n);

static inline uint32_t LvdsRxCameraOffset(uint32_t n)
{
    return (LVDSRX_CAM1_CFG + (LVDSRX_CAMERA_CFG_DIFF * n));
}

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshallvdsrxInstObj_t gIsshallvdsrxInstObjs[ISSHAL_LVDSRX_MAX_INST] =
{
    (uint32_t)FALSE
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_isslvdsrxInit(UInt32                          numInst,
                             const isshallvdsrxInstParams_t *instPrms,
                             Ptr                             arg)
{
    uint32_t instCnt;
    isshallvdsrxInstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_LVDSRX_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * lvdsrx number of instances. The size of this number of instances
         * is never more than ISSHAL_LVDSRX_MAX_INST.
         */
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].instId < ISSHAL_LVDSRX_INST_MAX_ID));

        pInstObj = &gIsshallvdsrxInstObjs[instCnt];

        if((uint32_t)FALSE == pInstObj->isInitDone)
        {
            pInstObj->openCnt        = 0U;
            pInstObj->instId         = instPrms[instCnt].instId;
            pInstObj->baseAddress    = instPrms[instCnt].baseAddress;
            pInstObj->maxPhys        = instPrms[instCnt].maxPhys;
            pInstObj->maxLanesPerPhy = instPrms[instCnt].maxLanesPerPhy;
            pInstObj->isInitDone     = (uint32_t)TRUE;
        }
    }

    return (FVID2_SOK);
}

int32_t VpsHal_isslvdsrxDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshallvdsrxInstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_LVDSRX_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIsshallvdsrxInstObjs[instCnt];

        /* None of the instance should be opened at this time */
        if(pInstObj->openCnt != 0)
        {
            GT_0trace(VpsHalTrace, GT_INFO,
                      "WARNING: ISS_LVDSRX: Instance openCnt is NOT zero !!!\n");
        }

        /* Reset instance id and base address */
        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
        pInstObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

VpsHal_Handle VpsHal_isslvdsrxOpen(
    const isshallvdsrxOpenParams_t *openPrms,
    Ptr                             arg)
{
    int32_t                status;
    uint32_t               instCnt;
    VpsHal_Handle          handle   = NULL;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0U; instCnt < ISSHAL_LVDSRX_MAX_INST; instCnt++)
    {
        pInstObj = &(gIsshallvdsrxInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == pInstObj->instId)
        {
            handle = (VpsHal_Handle) (pInstObj);

            /* Check whether some one has already opened this instance */
            if(0 == pInstObj->openCnt)
            {
                /* For the very first time, power up and reset */
                status = VpsHal_issPowerCtrl(SUB_MODULE_LVDSRX, TRUE);
                if(FVID2_SOK == status)
                {
                    /* LvdsrxReset(pInstObj); */
                }
                else
                {
                    GT_assert(VpsHalTrace, FALSE);
                    handle = NULL;
                }
            }

            pInstObj->openCnt++;
            break;
        }
    }

    return (handle);
}

int32_t VpsHal_isslvdsrxClose(VpsHal_Handle handle, Ptr arg)
{
    int32_t status = FVID2_EFAIL;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    /* Decrement the open count */
    if(pInstObj->openCnt > 0)
    {
        pInstObj->openCnt--;
        status = FVID2_SOK;
    }

    if(0U == pInstObj->openCnt)
    {
        status = VpsHal_issPowerCtrl(SUB_MODULE_LVDSRX, FALSE);
        GT_assert(VpsHalTrace, (FVID2_SOK == status));
    }

    return (status);
}

int32_t VpsHal_isslvdsrxSetConfig(VpsHal_Handle               handle,
                                  const isshallvdsrxConfig_t *cfg,
                                  Ptr                         arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal, temp;
    uint32_t cnt;
    uint32_t tempMask, diffMask;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    /* Check for the maximum number of phys and lanes per phy */
    if(pInstObj->maxPhys < cfg->numPhys)
    {
        status = FVID2_EINVALID_PARAMS;
    }
    else
    {
        for(cnt = 0U; cnt < cfg->numPhys; cnt++)
        {
            if(pInstObj->maxLanesPerPhy < cfg->numLanes[cnt])
            {
                status = FVID2_EINVALID_PARAMS;
                break;
            }
        }
    }

    /* Check the Bits per pixel */
    if((FVID2_BPP_BITS8 != cfg->bpp) &&
       (FVID2_BPP_BITS10 != cfg->bpp) &&
       (FVID2_BPP_BITS12 != cfg->bpp) &&
       (FVID2_BPP_BITS14 != cfg->bpp) &&
       (FVID2_BPP_BITS16 != cfg->bpp))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    /* Check for the maximum size */
    if((cfg->frameWidth >
        (LVDSRX_CAM1_FRMSIZE_LNWIDTH_MASK >>
         LVDSRX_CAM1_FRMSIZE_LNWIDTH_SHIFT)) ||
       (cfg->frameHeight >
        (LVDSRX_CAM1_FRMSIZE_FRWIDTH_MASK >>
         LVDSRX_CAM1_FRMSIZE_FRWIDTH_SHIFT)) ||
       (cfg->maxWidth >
        (LVDSRX_CAM1_MAXWIDTH_MASK >>
         LVDSRX_CAM1_MAXWIDTH_SHIFT)))
    {
        status = FVID2_EINVALID_PARAMS;
    }

    if(FVID2_SOK == status)
    {
        /* Set the Start VBlanking sync pattern */
        regVal =
            (cfg->sovblkPtn.bitMask << LVDSRX_CAM1_SYNCSOV_BITMASK_SHIFT) &
            LVDSRX_CAM1_SYNCSOV_BITMASK_MASK;
        regVal |=
            (cfg->sovblkPtn.pattern << LVDSRX_CAM1_SYNCSOV_SOFPTN_SHIFT) &
            LVDSRX_CAM1_SYNCSOV_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCSOV, regVal);

        /* Set the End of Line sync pattern */
        regVal = (cfg->eolPtn.bitMask << LVDSRX_CAM1_SYNCEOL_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCEOL_BITMASK_MASK;
        regVal |= (cfg->eolPtn.pattern << LVDSRX_CAM1_SYNCEOL_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCEOL_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCEOL, regVal);

        /* Set the Start of Line sync pattern */
        regVal = (cfg->solPtn.bitMask << LVDSRX_CAM1_SYNCSOL_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCSOL_BITMASK_MASK;
        regVal |= (cfg->solPtn.pattern << LVDSRX_CAM1_SYNCSOL_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCSOL_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCSOL, regVal);

        /* Set the End of Frame sync pattern */
        regVal = (cfg->eofPtn.bitMask << LVDSRX_CAM1_SYNCEOF_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCEOF_BITMASK_MASK;
        regVal |= (cfg->eofPtn.pattern << LVDSRX_CAM1_SYNCEOF_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCEOF_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCEOF, regVal);

        /* Set the Start of Frame sync pattern */
        regVal = (cfg->sofPtn.bitMask << LVDSRX_CAM1_SYNCSOF_BITMASK_SHIFT) &
                 LVDSRX_CAM1_SYNCSOF_BITMASK_MASK;
        regVal |= (cfg->sofPtn.pattern << LVDSRX_CAM1_SYNCSOF_SOFPTN_SHIFT) &
                  LVDSRX_CAM1_SYNCSOF_SOFPTN_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_SYNCSOF, regVal);

        /* Set the frame size */
        regVal = (cfg->frameWidth << LVDSRX_CAM1_FRMSIZE_LNWIDTH_SHIFT) &
                 LVDSRX_CAM1_FRMSIZE_LNWIDTH_MASK;
        regVal |= (cfg->frameHeight << LVDSRX_CAM1_FRMSIZE_FRWIDTH_SHIFT) &
                  LVDSRX_CAM1_FRMSIZE_FRWIDTH_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_FRMSIZE, regVal);

        /* Set the Max Frame width */
        regVal = HW_RD_REG32(pInstObj->baseAddress +
                             LvdsRxCameraOffset(cfg->inputCamId) +
                             LVDSRX_CAM_MAXWIDTH);
        regVal &= ~LVDSRX_CAM1_MAXWIDTH_MASK;
        regVal |= (cfg->maxWidth << LVDSRX_CAM1_MAXWIDTH_SHIFT) &
                  LVDSRX_CAM1_MAXWIDTH_MASK;
        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_MAXWIDTH, regVal);

        regVal = HW_RD_REG32(pInstObj->baseAddress +
                             LvdsRxCameraOffset(cfg->inputCamId) +
                             LVDSRX_CAM_CFG);

        regVal &= ~LVDSRX_CAM1_CFG_OP_MODE_MASK;
        regVal |= (cfg->opMode << LVDSRX_CAM1_CFG_OP_MODE_SHIFT) &
                  LVDSRX_CAM1_CFG_OP_MODE_MASK;

        regVal &= ~LVDSRX_CAM1_CFG_NUMPHY_MASK;
        regVal |= (cfg->numPhys << LVDSRX_CAM1_CFG_NUMPHY_SHIFT) &
                  LVDSRX_CAM1_CFG_NUMPHY_MASK;

        regVal &= ~LVDSRX_CAM1_CFG_PIX_WIDTH_MASK;
        if(FVID2_BPP_BITS8 == cfg->bpp)
        {
            temp   = (0x0U << LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal = regVal | temp;
        }
        else if(FVID2_BPP_BITS10 == cfg->bpp)
        {
            temp    = (0x1U << LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }
        else if(FVID2_BPP_BITS12 == cfg->bpp)
        {
            temp    = (0x2U << LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }
        else if(FVID2_BPP_BITS14 == cfg->bpp)
        {
            temp    = (0x3U << LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }
        else /* 16bpp */
        {
            temp    = (0x4U << LVDSRX_CAM1_CFG_PIX_WIDTH_SHIFT);
            regVal |= temp;
        }

        for(cnt = 0U; cnt < cfg->numPhys; cnt++)
        {
            diffMask = (LVDSRX_CAM1_CFG_NUM_LANE2_SHIFT -
                        LVDSRX_CAM1_CFG_NUM_LANE1_SHIFT) * cnt;

            tempMask =
                LVDSRX_CAM1_CFG_NUM_LANE1_MASK << diffMask;

            regVal &= ~tempMask;

            regVal |= (cfg->numLanes[cnt] <<
                       (LVDSRX_CAM1_CFG_NUM_LANE1_SHIFT + diffMask)) &
                      tempMask;
        }

        regVal &= ~LVDSRX_CAM1_CFG_CRCEN_MASK;
        if(TRUE == cfg->enableCrcCheck)
        {
            regVal |= LVDSRX_CAM1_CFG_CRCEN_MASK;
        }

        regVal &= ~LVDSRX_CAM1_CFG_DENDIAN_MASK;
        if(TRUE == cfg->enableDataBigEndian)
        {
            regVal |= LVDSRX_CAM1_CFG_DENDIAN_MASK;
        }

        regVal &= ~LVDSRX_CAM1_CFG_SENDIAN_MASK;
        if(TRUE == cfg->enableSyncBigEndian)
        {
            regVal |= LVDSRX_CAM1_CFG_SENDIAN_MASK;
        }

        regVal &= ~LVDSRX_CAM1_CFG_FILEN_MASK;
        if(TRUE == cfg->enableFiller)
        {
            regVal |= LVDSRX_CAM1_CFG_FILEN_MASK;
        }

        regVal &= ~LVDSRX_CAM1_CFG_ALIGN_MASK;
        if(TRUE == cfg->enableMsbAlign)
        {
            regVal |= LVDSRX_CAM1_CFG_ALIGN_MASK;
        }

        /* TODO: Configure SENDIAN, DENDIAN, FRSTATE ?? */

        HW_WR_REG32(pInstObj->baseAddress +
                    LvdsRxCameraOffset(cfg->inputCamId) +
                    LVDSRX_CAM_CFG, regVal);
    }

    return (status);
}

int32_t VpsHal_isslvdsrxControl(VpsHal_Handle handle,
                                UInt32        cmd,
                                Ptr           cmdArgs,
                                Ptr           arg)
{
    return (FVID2_SOK);
}

int32_t VpsHal_isslvdsrxStart(
    VpsHal_Handle               handle,
    issCtrlProcMode_t           procMode,
    isshallvdsrxInputCameraId_t inputCamId)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG);

    if(ISSHAL_LVDSRX_INPUT_CAM_ID0 == inputCamId)
    {
        regVal |= LVDSRX_CAMCFG_CAM1ENA_ENABLE;
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID1 == inputCamId)
    {
        regVal |= LVDSRX_CAMCFG_CAM2ENA_ENABLE;
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID2 == inputCamId)
    {
        regVal |= LVDSRX_CAMCFG_CAM3ENA_ENABLE;
    }
    else
    {
        regVal |= LVDSRX_CAMCFG_CAM4ENA_ENABLE;
    }

    HW_WR_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG, regVal);

    return (status);
}

int32_t VpsHal_isslvdsrxStop(
    VpsHal_Handle               handle,
    isshallvdsrxInputCameraId_t inputCamId)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG);

    if(ISSHAL_LVDSRX_INPUT_CAM_ID0 == inputCamId)
    {
        regVal &= ~LVDSRX_CAMCFG_CAM1ENA_ENABLE;
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID1 == inputCamId)
    {
        regVal &= ~LVDSRX_CAMCFG_CAM2ENA_ENABLE;
    }
    else if(ISSHAL_LVDSRX_INPUT_CAM_ID2 == inputCamId)
    {
        regVal &= ~LVDSRX_CAMCFG_CAM3ENA_ENABLE;
    }
    else
    {
        regVal &= ~LVDSRX_CAMCFG_CAM4ENA_ENABLE;
    }

    HW_WR_REG32(pInstObj->baseAddress + LVDSRX_CAMCFG, regVal);

    return (status);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

Void LvdsrxReset(VpsHal_Handle handle)
{
    uint32_t tempCnt;
    uint32_t regVal;
    isshallvdsrxInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshallvdsrxInstObj_t *) handle;

    /* Assert the reset */
    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG);
    regVal = regVal | LVDSRX_SYSCONFIG_RESERVED_MASK;
    HW_WR_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG, regVal);

    regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG);

    /* Waits until reset is done */
    tempCnt = 0xFFFFU;
#ifdef PLATFORM_EVM_SI
    while((0x0U != tempCnt) &&
          (regVal != LVDSRX_SYSCONFIG_RESERVED_PENDING))
    {
        tempCnt--;
        regVal = HW_RD_REG32(pInstObj->baseAddress + LVDSRX_SYSCONFIG);
    }
#endif

    GT_assert(VpsHalTrace, (0U < tempCnt));
}

