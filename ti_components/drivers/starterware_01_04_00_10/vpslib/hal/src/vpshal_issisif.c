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
 *  \file isshal_isif.c
 *
 *  \brief File containing the ISS ISIF HAL init, deinit and other common
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
#include <common/bsp_utils.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <hw/hw_iss_isif.h>
#include <hw/hw_types.h>
#include <fvid2/fvid2_dataTypes.h>
#include <hal/vpshal.h>
#include <hal/vpshal_iss.h>
#include <hal/vpshal_issisif.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**< Time to wait in worst case for table clear to complete */
#define ISS_HAL_ISIF_VFDC_MEM_TABLE_CLEAR_WAIT      (0xFFFU)

/**< Time to wait in worst case for internal write to table complete */
#define ISS_HAL_ISIF_VFDC_MEM_TABLE_WRITE_WAIT      (0xFFFU)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct isshalisifInstObj
{
    uint32_t isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t instId;
    /**< Id of the instance */
    uint32_t baseAddress;
    /**< Register base address */
    uint32_t openCnt;
    /**< Open count */
} isshalisifInstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t IsifSetSrcConfig(
    const isshalisifInstObj_t   *pInstObj,
    const isshalisifSrcConfig_t *srcCfg);

static int32_t IsifSetGainOffsetConfig(
    const isshalisifInstObj_t        *pInstObj,
    const isshalisifGainOfstConfig_t *wbCfg);

static int32_t IsifSetVfdcConfig(
    const isshalisifInstObj_t *pInstObj,
    isshalisifVfdcConfig_t    *pVfdcCfg);

static int32_t IsifSetVfdcTableUpdate(
    const isshalisifInstObj_t *pInstObj,
    isshalisifVfdcConfig_t    *pVfdcCfg);

static int32_t IsifSetBlackClampConfig(
    const isshalisifInstObj_t          *pInstObj,
    const isshalisifBlackClampConfig_t *pBlkClampCfg);

static int32_t IsifSet2DLscConfig(
    const isshalisifInstObj_t     *pInstObj,
    const vpsissIsif2DLscConfig_t *p2dLscCfg);

static int32_t IsifSetInFrmSize(
    const isshalisifInstObj_t   *pInstObj,
    const isshalisifSrcConfig_t *srcCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalisifInstObj_t      gIssHalIsifInstObjs[ISSHAL_ISIF_MAX_INST] =
{(uint32_t)FALSE};

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalIsifDefCfg' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static const isshalisifConfig_t gIssHalIsifDefCfg =
{
    ISSHAL_ISIF_MODULE_SRC_CFG | ISSHAL_ISIF_MODULE_GAIN_OFST_CFG |
    ISSHAL_ISIF_MODULE_VFDC_CFG,
    {
        FALSE,                           /* Is HD/VD *Out */
        FALSE,                           /* Is FID out **/
        FALSE,                           /* Is Data Inverted */
        FVID2_POL_HIGH,                  /* HD Polarity */
        FVID2_POL_HIGH,                  /* VD Polarity */
        FVID2_DF_BAYER_RGGB,             /* Data Format */
        FVID2_VIFW_8BIT,                 /* Video Interface width for YUV */
        2U,                              /* hd Width */
        2U,                              /* vd Width */
        2U,                              /* Pixels per line */
        2U,                              /* Lines per frame */
        ISSHAL_ISIF_INPUT_MSB_POS_BIT12, /* MSB Position */
        ISSHAL_ISIF_CFG_PATTERN_MOSAIC,
        FALSE                            /* Swap at input MS & LS Byte*/
    },
    {
        {0x0U,                               0x0U,
         0x0U,                               0x0U},
        0x0U,
        {FALSE,                              FALSE,
         FALSE},
        {FALSE,                              FALSE,
         FALSE}
    },
    /* VFDC Default config - disabled */
    {
        VPS_ISS_ISIF_VDFC_DISABLE,           /* mode = Disabled */
        0x0U,                                /* shiftUp */
        0x0U,                                /* correctAbovePixels */
        0x0U,                                /* satVal */
        {
            {0x0U,                           0x0U,
             0x0U,                           0x0U,  0x0U,  0x0U,
             0x0U,                           0x0U},
            {0x0U,                           0x0U,  0x0U,  0x0U,0x0U,  0x0U,
             0x0U,                           0x0U},
            {0x0U,                           0x0U,  0x0U,  0x0U,0x0U,  0x0U,
             0x0U,                           0x0U}
        },
        0x0U,                                /* numPixToBeCorrected */
        {
            {0x0U,                           0x0U,  0x0U,  0x0U,0x0U,  0x0U,
             0x0U,                           0x0U},
            {0x0U,                           0x0U,  0x0U,  0x0U,0x0U,  0x0U,
             0x0U,                           0x0U}
        }
    },
    /* Black Clamping parameters,
       Only DC Offset is supported as of now */
    {
        0x0U
    },
    /* 2D LSC Configuration */
    {
        0U,
        {0U,                                 0U,    0U,    0U},
        {0U,                                 0U},
        VPS_ISS_ISIF_2D_LSC_DS_8,
        VPS_ISS_ISIF_2D_LSC_DS_8,
        VPS_ISS_ISIF_2D_LSC_GAIN_FORMAT_U8Q8,
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
        VPS_ISS_ISIF_2D_LSC_OFFSET_SHIFT_0
    }
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_issisifInit(UInt32                        numInst,
                           const isshalisifInstParams_t *instPrms,
                           Ptr                           arg)
{
    uint32_t instCnt;
    isshalisifInstObj_t *pInstObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= ISSHAL_ISIF_MAX_INST));
    GT_assert(VpsHalTrace, (NULL != instPrms));

    /* Set the default Values for non-changing parameters */
    for(instCnt = 0U; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (NULL != instPrms));
        GT_assert(VpsHalTrace,
                  (instPrms->instId < ISSHAL_ISIF_INST_MAX_ID));
        GT_assert(VpsHalTrace,
                  (NULL != instPrms->baseAddress));

        pInstObj = &gIssHalIsifInstObjs[instCnt];

        if((uint32_t)FALSE == pInstObj->isInitDone)
        {
            pInstObj->openCnt     = 0U;
            pInstObj->instId      = instPrms->instId;
            pInstObj->baseAddress = instPrms->baseAddress;
            pInstObj->isInitDone  = (uint32_t)TRUE;
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
         * Pointer is accessed as an array
         * KW State: Defer -> Waiver -> Case by case
         * MISRAC_WAIVER: Pointer is accessed as an array.
         * This function is called by init function, which passes
         * isif number of instances. The size of this number of instances
         * is never more than ISSHAL_ISIF_MAX_INST.
         */
        instPrms++;
    }

    return (BSP_SOK);
}

int32_t VpsHal_issisifDeInit(Ptr arg)
{
    uint32_t instCnt;
    isshalisifInstObj_t *pInstObj;

    for(instCnt = 0U; instCnt < ISSHAL_ISIF_INST_MAX_ID; instCnt++)
    {
        pInstObj = &gIssHalIsifInstObjs[instCnt];

        GT_assert(VpsHalTrace, (0U == pInstObj->openCnt));

        pInstObj->instId      = 0x0U;
        pInstObj->baseAddress = 0x0U;
        pInstObj->isInitDone  = (uint32_t)FALSE;
    }

    return (FVID2_SOK);
}

VpsHal_Handle VpsHal_issisifOpen(const isshalOpenParams_t *openPrms,
                                 Ptr                       arg)
{
    uint32_t             instCnt;
    VpsHal_Handle        handle   = NULL;
    isshalisifInstObj_t *pInstObj = NULL;

    /* Check for errors */
    GT_assert(VpsHalTrace, (NULL != openPrms));

    for(instCnt = 0; instCnt < ISSHAL_ISIF_MAX_INST; instCnt++)
    {
        pInstObj = &(gIssHalIsifInstObjs[instCnt]);

        /* Return the matching instance handle */
        if(openPrms->instId == pInstObj->instId)
        {
            handle = (VpsHal_Handle) pInstObj;

            /* Enable Module clock on first instance */
            if(0 == pInstObj->openCnt)
            {
                /* Enable ISIF Module at the ISS level */
                GT_assert(
                    VpsHalTrace,
                    (FVID2_SOK ==
                     VpsHal_issEnableModule(
                         ISSHAL_ISS_MODULE_ISIF,
                         TRUE)));
            }

            pInstObj->openCnt++;
            break;
        }
    }

    return (handle);
}

int32_t VpsHal_issisifClose(VpsHal_Handle handle,
                            Ptr           arg)
{
    int32_t status = FVID2_EFAIL;
    isshalisifInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalisifInstObj_t *) handle;

    /* Decrement the open count */
    if(pInstObj->openCnt > 0)
    {
        pInstObj->openCnt--;

        if(0U == pInstObj->openCnt)
        {
            /* Disable ISIF Module at the ISS level */
            GT_assert(
                VpsHalTrace,
                (FVID2_SOK ==
                 VpsHal_issEnableModule(
                     ISSHAL_ISS_MODULE_ISIF,
                     FALSE)));
        }
        status = FVID2_SOK;
    }

    return (status);
}

int32_t VpsHal_issisifSetConfig(VpsHal_Handle       handle,
                                isshalisifConfig_t *cfg,
                                Ptr                 arg)
{
    int32_t  status = FVID2_SOK;
    uint32_t moduleId;
    isshalisifInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != cfg));

    pInstObj = (isshalisifInstObj_t *) handle;

    moduleId = (uint32_t) cfg->moduleId;

    while(0U < moduleId)
    {
        if((ISSHAL_ISIF_MODULE_SRC_CFG & moduleId) ==
           ISSHAL_ISIF_MODULE_SRC_CFG)
        {
            moduleId &= ~ISSHAL_ISIF_MODULE_SRC_CFG;
            status    = IsifSetSrcConfig(pInstObj, &cfg->srcCfg);
        }
        else if((ISSHAL_ISIF_MODULE_GAIN_OFST_CFG & moduleId) ==
                ISSHAL_ISIF_MODULE_GAIN_OFST_CFG)
        {
            moduleId &= ~ISSHAL_ISIF_MODULE_GAIN_OFST_CFG;
            status    = IsifSetGainOffsetConfig(pInstObj, &cfg->wbCfg);
        }
        else if((ISSHAL_ISIF_MODULE_VFDC_CFG & moduleId) ==
                ISSHAL_ISIF_MODULE_VFDC_CFG)
        {
            moduleId &= ~ISSHAL_ISIF_MODULE_VFDC_CFG;
            status    = IsifSetVfdcConfig(pInstObj, &cfg->vfdcCfg);
        }
        else if((ISSHAL_ISIF_MODULE_BLACK_CLAMP_CFG & moduleId) ==
                ISSHAL_ISIF_MODULE_BLACK_CLAMP_CFG)
        {
            moduleId &= ~ISSHAL_ISIF_MODULE_BLACK_CLAMP_CFG;
            status    = IsifSetBlackClampConfig(
                pInstObj,
                &cfg->blkClampCfg);
        }
        else if((ISSHAL_ISIF_MODULE_2D_LSC_CFG & moduleId) ==
                ISSHAL_ISIF_MODULE_2D_LSC_CFG)
        {
            moduleId &= ~ISSHAL_ISIF_MODULE_2D_LSC_CFG;
            status    = IsifSet2DLscConfig(
                pInstObj,
                &cfg->lscCfg);
        }
        else
        {
            /* No matching module id */
            status = FVID2_EINVALID_PARAMS;
        }

        if(status != FVID2_SOK)
        {
            break;
        }
    }

    return (status);
}

int32_t VpsHal_issisifGetConfig(VpsHal_Handle       handle,
                                isshalisifConfig_t *config)
{
    return (FVID2_SOK);
}

int32_t VpsHal_issisifControl(VpsHal_Handle handle,
                              UInt32        cmd,
                              Ptr           cmdArgs,
                              Ptr           arg)
{
    int32_t status = FVID2_SOK;
    isshalisifInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalisifInstObj_t *) handle;

    switch(cmd)
    {
        /* Case is to set white balance/Gain Offset Configuration */
        case ISSHAL_IOCTL_ISIF_SET_WBCFG:
            status = IsifSetGainOffsetConfig(
                pInstObj,
                (const isshalisifGainOfstConfig_t *)cmdArgs);
            break;
        case ISSHAL_IOCTL_ISIF_SET_IP_FRM_SIZE:
            status = IsifSetInFrmSize(pInstObj,
                                      (isshalisifSrcConfig_t *) cmdArgs);
            break;
        case ISSHAL_IOCTL_ISIF_SET_VFDC_CFG:
            status = IsifSetVfdcConfig(
                pInstObj,
                (isshalisifVfdcConfig_t *) cmdArgs);
            break;
        case ISSHAL_IOCTL_ISIF_SET_BLACK_CLAMP_CFG:
            status = IsifSetBlackClampConfig(
                pInstObj,
                (isshalisifBlackClampConfig_t *) cmdArgs);
            break;
        case ISSHAL_IOCTL_ISIF_SET_2D_LSC_CFG:
            status = IsifSet2DLscConfig(
                pInstObj,
                (vpsissIsif2DLscConfig_t *) cmdArgs);
            break;
        case ISSHAL_IOCTL_ISIF_GET_DEFAULTCFG:
            if(NULL != cmdArgs)
            {
                BspUtils_memcpy(
                    (isshalisifConfig_t *) cmdArgs,
                    &gIssHalIsifDefCfg,
                    sizeof(isshalisifConfig_t));
            }
            else
            {
                status = FVID2_EBADARGS;
            }
            break;
        case VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO:
        {
            isshalissBlankingInfo_t *blankInfo =
                (isshalissBlankingInfo_t *) cmdArgs;

            GT_assert(VpsHalTrace, (NULL != blankInfo));

            blankInfo->hBlank = blankInfo->vBlank = 0U;
            break;
        }
        case VPS_HAL_ISS_IOCTL_START:
        {
            HW_WR_REG32(pInstObj->baseAddress + ISIF_SYNCEN,
                        HW_RD_REG32(pInstObj->baseAddress + ISIF_SYNCEN) |
                        ISIF_SYNCEN_SYEN_MASK);
            break;
        }
        case VPS_HAL_ISS_IOCTL_STOP:
        {
            /* Disable IPIPE */
            HW_WR_REG32(pInstObj->baseAddress + ISIF_SYNCEN,
                        (HW_RD_REG32(pInstObj->baseAddress + ISIF_SYNCEN) &
                         ~ISIF_SYNCEN_SYEN_MASK));
            break;
        }
        default:
            status = FVID2_EUNSUPPORTED_CMD;
            break;
    }

    return (status);
}

int32_t VpsHal_issisifStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    volatile uint32_t    regVal;
    isshalisifInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalisifInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + ISIF_SYNCEN);

    regVal |= ISIF_SYNCEN_SYEN_MASK;

#ifdef VPSCORE_ENABLE_ISIF_WRITE
    regVal |= ISIF_SYNCEN_SYEN_MASK | ISIF_SYNCEN_DWEN_MASK;
#endif /* VPSCORE_ENABLE_ISIF_WRITE */
    HW_WR_REG32(pInstObj->baseAddress + ISIF_SYNCEN, regVal);

    return (FVID2_SOK);
}

int32_t VpsHal_issisifStop(VpsHal_Handle handle, Ptr arg)
{
    volatile uint32_t    regVal;
    isshalisifInstObj_t *pInstObj = NULL;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    pInstObj = (isshalisifInstObj_t *) handle;

    regVal = HW_RD_REG32(pInstObj->baseAddress + ISIF_SYNCEN);
#ifdef VPSCORE_ENABLE_ISIF_WRITE
    regVal &= ~(ISIF_SYNCEN_SYEN_MASK | ISIF_SYNCEN_DWEN_MASK);
#endif /* VPSCORE_ENABLE_ISIF_WRITE */
    regVal &= ~ISIF_SYNCEN_SYEN_MASK;

    HW_WR_REG32(pInstObj->baseAddress + ISIF_SYNCEN, regVal);

    return (FVID2_SOK);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t IsifSetSrcConfig(
    const isshalisifInstObj_t   *pInstObj,
    const isshalisifSrcConfig_t *srcCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != srcCfg));

    /* Set the MSB Position and CFA Pattern in CGAMMAWD Register */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CGAMMAWD);
    regVal &= ~ISIF_CGAMMAWD_CFAP_MASK;
    if(ISSHAL_ISIF_CFG_PATTERN_STRIP == srcCfg->cfaPattern)
    {
        regVal |= ISIF_CGAMMAWD_CFAP_MASK;
    }

    regVal &= ~ISIF_CGAMMAWD_GWDI_MASK;
    regVal |= ((uint32_t) srcCfg->msbPos << ISIF_CGAMMAWD_GWDI_SHIFT) &
              ISIF_CGAMMAWD_GWDI_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_CGAMMAWD, regVal);

    /* Set the Bayer color Pattern in CCOLP Register */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CCOLP);
    regVal &= ~(ISIF_CCOLP_CP3_F0_MASK | ISIF_CCOLP_CP2_F0_MASK |
                ISIF_CCOLP_CP1_F0_MASK | ISIF_CCOLP_CP0_F0_MASK);
    regVal &= ~(ISIF_CCOLP_CP3_F1_MASK | ISIF_CCOLP_CP2_F1_MASK |
                ISIF_CCOLP_CP1_F1_MASK | ISIF_CCOLP_CP0_F1_MASK);

    if((Int32)TRUE == Fvid2_isDataFmtBayer(srcCfg->inDataFormat))
    {
        if(FVID2_DF_BAYER_GRBG == srcCfg->inDataFormat)
        {
            /* Gr R   1 0
             * B  Gb  3 2 */
            regVal |= ISIF_CCOLP_CP0_F0_NEWENUM2 | ISIF_CCOLP_CP1_F0_NEWENUM1 |
                      ISIF_CCOLP_CP2_F0_NEWENUM4 | ISIF_CCOLP_CP3_F0_NEWENUM3;
            regVal |= ISIF_CCOLP_CP0_F1_NEWENUM2 | ISIF_CCOLP_CP1_F1_NEWENUM1 |
                      ISIF_CCOLP_CP2_F1_NEWENUM4 | ISIF_CCOLP_CP3_F1_NEWENUM3;
        }
        else if(FVID2_DF_BAYER_RGGB == srcCfg->inDataFormat)
        {
            /* R  Gr  0 1
             * Gb  B  2 3 */
            regVal |= ISIF_CCOLP_CP0_F0_NEWENUM1 | ISIF_CCOLP_CP1_F0_NEWENUM2 |
                      ISIF_CCOLP_CP2_F0_NEWENUM3 | ISIF_CCOLP_CP3_F0_NEWENUM4;
            regVal |= ISIF_CCOLP_CP0_F1_NEWENUM1 | ISIF_CCOLP_CP1_F1_NEWENUM2 |
                      ISIF_CCOLP_CP2_F1_NEWENUM3 | ISIF_CCOLP_CP3_F1_NEWENUM4;
        }
        else if(FVID2_DF_BAYER_BGGR == srcCfg->inDataFormat)
        {
            /* B  Gb  3 2
             * Gr R   1 0 */
            regVal |= ISIF_CCOLP_CP0_F0_NEWENUM4 | ISIF_CCOLP_CP1_F0_NEWENUM3 |
                      ISIF_CCOLP_CP2_F0_NEWENUM2 | ISIF_CCOLP_CP3_F0_NEWENUM1;
            regVal |= ISIF_CCOLP_CP0_F1_NEWENUM4 | ISIF_CCOLP_CP1_F1_NEWENUM3 |
                      ISIF_CCOLP_CP2_F1_NEWENUM2 | ISIF_CCOLP_CP3_F1_NEWENUM1;
        }
        else /* FVID2_DF_BAYER_GBRG */
        {
            /* Gb  B  2 3
             * R  Gr  0 1 */
            regVal |= ISIF_CCOLP_CP0_F0_NEWENUM3 | ISIF_CCOLP_CP1_F0_NEWENUM4 |
                      ISIF_CCOLP_CP2_F0_NEWENUM1 | ISIF_CCOLP_CP3_F0_NEWENUM2;
            regVal |= ISIF_CCOLP_CP0_F1_NEWENUM3 | ISIF_CCOLP_CP1_F1_NEWENUM4 |
                      ISIF_CCOLP_CP2_F1_NEWENUM1 | ISIF_CCOLP_CP3_F1_NEWENUM2;
        }
    }
    HW_WR_REG32(pInstObj->baseAddress + ISIF_CCOLP, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CCDCFG);
    regVal &= ~ISIF_CCDCFG_YCINSWP_MASK;
    if(TRUE == srcCfg->ycInSwap)
    {
        regVal |= ISIF_CCDCFG_YCINSWP_MASK;
    }
    HW_WR_REG32(pInstObj->baseAddress + ISIF_CCDCFG, regVal);

    /* Set the HD/VD width and HD/VD Period */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_HDW);
    regVal &= ~ISIF_HDW_MASK;
    regVal |= ((srcCfg->hdWidth - 1U) << ISIF_HDW_SHIFT) & ISIF_HDW_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_HDW, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDW);
    regVal &= ~ISIF_VDW_MASK;
    regVal |= ((srcCfg->vdWidth - 1U) << ISIF_VDW_SHIFT) & ISIF_VDW_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDW, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_PPLN);
    regVal &= ~ISIF_PPLN_MASK;
    regVal |= ((srcCfg->pixelsPerLine - 1U) << ISIF_PPLN_SHIFT) &
              ISIF_PPLN_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_PPLN, regVal);

    /* Set the HD Period */
    /* Sets number of half lines per frame or field.
     * VD period = (LPFR+1)/2 lines.*/
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_LPFR);
    regVal &= ~ISIF_LPFR_MASK;
    regVal |= (((srcCfg->linesPerFrame * 2U) - 1U) << ISIF_LPFR_SHIFT) &
              ISIF_LPFR_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_LPFR, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDINT0);
    regVal &= ~ISIF_VDINT0_CVD0_MASK;
    regVal |= ((srcCfg->linesPerFrame - 1U) << ISIF_VDINT0_CVD0_SHIFT) &
              ISIF_VDINT0_CVD0_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDINT0, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDINT1);
    regVal &= ~ISIF_VDINT1_CVD1_MASK;
    regVal |= ((srcCfg->linesPerFrame - 1U) << ISIF_VDINT1_CVD1_SHIFT) &
              ISIF_VDINT1_CVD1_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDINT1, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDINT2);
    regVal &= ~ISIF_VDINT2_CVD2_MASK;
    regVal |= ((srcCfg->linesPerFrame - 1U) << ISIF_VDINT2_CVD2_SHIFT) &
              ISIF_VDINT2_CVD2_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDINT2, regVal);

    /* Set the Polariry/directions/input format in MODESET Register */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_MODESET);
    regVal &= ~ISIF_MODESET_INPMOD_MASK;

    if(((Int32)TRUE == Fvid2_isDataFmtYuv422(srcCfg->inDataFormat)) ||
       (((Int32)TRUE == Fvid2_isDataFmtYuv420(srcCfg->inDataFormat))))
    {
        if(FVID2_VIFW_8BIT == srcCfg->vidIfWidth)
        {
            regVal |= ISIF_MODESET_INPMOD_NEWENUM3;
        }
        else
        {
            regVal |= ISIF_MODESET_INPMOD_NEWENUM2;
        }
    }
    else /* Raw Mode */
    {
        regVal |= ISIF_MODESET_INPMOD_NEWENUM1;
    }

    regVal &= ~ISIF_MODESET_HDVDD_MASK;
    if(TRUE == srcCfg->isHdVdOut)
    {
        regVal |= ISIF_MODESET_HDVDD_MASK;
    }

    regVal &= ~ISIF_MODESET_FIDD_MASK;
    if(TRUE == srcCfg->isFidOut)
    {
        regVal |= ISIF_MODESET_FIDD_MASK;
    }

    regVal &= ~ISIF_MODESET_DPOL_MASK;
    if(TRUE == srcCfg->isInDataInvt)
    {
        regVal |= ISIF_MODESET_DPOL_MASK;
    }

    regVal &= ~ISIF_MODESET_HDPOL_MASK;
    if(FVID2_POL_LOW == srcCfg->hdPol)
    {
        regVal |= ISIF_MODESET_HDPOL_MASK;
    }

    regVal &= ~ISIF_MODESET_VDPOL_MASK;
    if(FVID2_POL_LOW == srcCfg->vdPol)
    {
        regVal |= ISIF_MODESET_VDPOL_MASK;
    }
    HW_WR_REG32(pInstObj->baseAddress + ISIF_MODESET, regVal);

    return (status);
}

static int32_t IsifSetGainOffsetConfig(
    const isshalisifInstObj_t        *pInstObj,
    const isshalisifGainOfstConfig_t *wbCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));

    if(NULL == wbCfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        /* Set the Gain */
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CRGAIN);
        regVal &= ~ISIF_CRGAIN_CGR_MASK;
        regVal |= (wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_R] <<
                   ISIF_CRGAIN_CGR_SHIFT) &
                  ISIF_CRGAIN_CGR_MASK;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CRGAIN, regVal);

        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CGRGAIN);
        regVal &= ~ISIF_CGRGAIN_CGGR_MASK;
        regVal |= (wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_GR] <<
                   ISIF_CGRGAIN_CGGR_SHIFT) &
                  ISIF_CGRGAIN_CGGR_MASK;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CGRGAIN, regVal);

        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CGBGAIN);
        regVal &= ~ISIF_CGBGAIN_CGGB_MASK;
        regVal |= (wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_GB] <<
                   ISIF_CGBGAIN_CGGB_SHIFT) &
                  ISIF_CGBGAIN_CGGB_MASK;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CGBGAIN, regVal);

        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CBGAIN);
        regVal &= ~ISIF_CBGAIN_CGB_MASK;
        regVal |= (wbCfg->gain[ISSHAL_ISS_BAYER_COLOR_COMP_B] <<
                   ISIF_CBGAIN_CGB_SHIFT) &
                  ISIF_CBGAIN_CGB_MASK;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CBGAIN, regVal);

        /* Set the Offset */
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_COFSTA);
        regVal &= ~ISIF_COFSTA_COFT_MASK;
        regVal |= (wbCfg->offset << ISIF_COFSTA_COFT_SHIFT) &
                  ISIF_COFSTA_COFT_MASK;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_COFSTA, regVal);

        /* Enable the Gain and Offset for the three outputs */
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CGAMMAWD);
        regVal &= ~ISIF_CGAMMAWD_WBEN0_MASK;
        if(TRUE == wbCfg->gainEnable[VPS_ISS_ISIF_OUTPUT_MEMORY])
        {
            regVal |= ISIF_CGAMMAWD_WBEN0_MASK;
        }

        regVal &= ~ISIF_CGAMMAWD_WBEN1_MASK;
        if(TRUE == wbCfg->gainEnable[VPS_ISS_ISIF_OUTPUT_IPIPE])
        {
            regVal |= ISIF_CGAMMAWD_WBEN1_MASK;
        }

        regVal &= ~ISIF_CGAMMAWD_WBEN2_MASK;
        if(TRUE == wbCfg->gainEnable[VPS_ISS_ISIF_OUTPUT_H3A])
        {
            regVal |= ISIF_CGAMMAWD_WBEN2_MASK;
        }

        regVal &= ~ISIF_CGAMMAWD_OFSTEN0_MASK;
        if(TRUE == wbCfg->offsetEnable[VPS_ISS_ISIF_OUTPUT_MEMORY])
        {
            regVal |= ISIF_CGAMMAWD_OFSTEN0_MASK;
        }

        regVal &= ~ISIF_CGAMMAWD_OFSTEN1_MASK;
        if(TRUE == wbCfg->offsetEnable[VPS_ISS_ISIF_OUTPUT_IPIPE])
        {
            regVal |= ISIF_CGAMMAWD_OFSTEN1_MASK;
        }

        regVal &= ~ISIF_CGAMMAWD_OFSTEN2_MASK;
        if(TRUE == wbCfg->offsetEnable[VPS_ISS_ISIF_OUTPUT_H3A])
        {
            regVal |= ISIF_CGAMMAWD_OFSTEN2_MASK;
        }
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CGAMMAWD, regVal);
    }

    return (status);
}

/**  \brief Function to configure Vertical Line defect correction sub-blocks.
            Perfroms NO error checks. Caller ensure all config is valid */
static int32_t IsifSetVfdcConfig(
    const isshalisifInstObj_t *pInstObj,
    isshalisifVfdcConfig_t    *pVfdcCfg)
{
    int32_t  status;
    uint32_t regVal;

    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != pVfdcCfg));
    GT_assert(VpsHalTrace, (NULL != pInstObj->baseAddress));

    /* If enabled, configure the reset, else disable and exit */
    status = FVID2_SOK;

    if(VPS_ISS_ISIF_VDFC_DISABLE != pVfdcCfg->mode)
    {
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCCTL);
        regVal &= ~(ISIF_DFCCTL_VDFCSL_MASK | ISIF_DFCCTL_VDFCUDA_MASK |
                    ISIF_DFCCTL_VDFLSFT_MASK | ISIF_DFCCTL_VDFCEN_MASK);
        regVal |= ISIF_DFCCTL_VDFCSL_MASK &
                  (pVfdcCfg->mode << ISIF_DFCCTL_VDFCSL_SHIFT);
        regVal |= ISIF_DFCCTL_VDFCUDA_MASK &
                  (pVfdcCfg->correctAbovePixels << ISIF_DFCCTL_VDFCUDA_SHIFT);
        regVal |= ISIF_DFCCTL_VDFLSFT_MASK &
                  (pVfdcCfg->shiftUp << ISIF_DFCCTL_VDFLSFT_SHIFT);
        HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCCTL, regVal);

        regVal = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDFSATLV);
        regVal = ISIF_VDFSATLV_VDFSLV_MASK &
                 (pVfdcCfg->satVal << ISIF_VDFSATLV_VDFSLV_SHIFT);
        HW_WR_REG32(pInstObj->baseAddress + ISIF_VDFSATLV, regVal);

        status = IsifSetVfdcTableUpdate(pInstObj, pVfdcCfg);
        if(FVID2_SOK == status)
        {
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCCTL);
            regVal |= ISIF_DFCCTL_VDFCEN_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCCTL, regVal);
        }
    }
    else
    {
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCCTL);
        regVal &= ~ISIF_DFCCTL_VDFCEN_MASK;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCCTL, regVal);
    }

    return status;
}

/**  \brief Function to configure Vertical Line defect correction sub-blocks
            defect pixel co-ordinates and defect level values.
            Caller ensures that VFDC is not enabled */
static int32_t IsifSetVfdcTableUpdate(
    const isshalisifInstObj_t *pInstObj,
    isshalisifVfdcConfig_t    *pVfdcCfg)
{
    int32_t           status;
    uint32_t          regVal, idx;
    volatile uint32_t timeOut;

    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != pVfdcCfg));
    GT_assert(VpsHalTrace, (NULL != pInstObj->baseAddress));

    /* Steps
        . Clear the existing memory table
        . Repeat for 8
        .. if defined use provided value
        .. else compute value as follows
        ... Set V Co-Ordinate to 0x0
        ... Set H Co-Ordinate to 0xFFFF
        .. Write V Co-Ordinate
        .. Write H Co-Ordinate
        .. Write Defect level for defect pixel
        .. Write Defect level for pixels above defect pixel
        .. Write Defect level for pixels below defect pixel
        .. For very first write
        ... Set to reset the table address offset to 0x0
        .. Else
        ... Set to increment table address offset
        .. Enable write to table - wait for this bit to clear
        */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL);
    regVal |= ISIF_DFCMEMCTL_DFCMCLR_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL, regVal);

    status  = FVID2_SOK;
    timeOut = ISS_HAL_ISIF_VFDC_MEM_TABLE_CLEAR_WAIT;
    while((0U < timeOut) && (0U != (regVal & ISIF_DFCMEMCTL_DFCMCLR_MASK)))
    {
        regVal = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL);
        timeOut--;
    }
    if(0x0U != timeOut)
    {
        /* Check less than 8 pixels are to be corrected. If so mark the
            non-defined pixels as invalid */
        if(VPS_ISS_ISIF_VFDC_MAX_PIX_CORR != pVfdcCfg->numPixToBeCorrected)
        {
            for(idx = pVfdcCfg->numPixToBeCorrected;
                idx < VPS_ISS_ISIF_VFDC_MAX_PIX_CORR; idx++)
            {
                /* V Value */
                pVfdcCfg->defectivePixCoOr[0][idx] = 0x0;
                /* H Value */
                pVfdcCfg->defectivePixCoOr[1][idx] = 0xFFFFFFFFU;
                pVfdcCfg->subtractValues[0][idx]   = 0x0;
                pVfdcCfg->subtractValues[1][idx]   = 0x0;
                pVfdcCfg->subtractValues[2][idx]   = 0x0;
            }
        }
        pVfdcCfg->numPixToBeCorrected = VPS_ISS_ISIF_VFDC_MAX_PIX_CORR;

        /* Write pix locations / defect values */
        for(idx = 0U; ((idx < VPS_ISS_ISIF_VFDC_MAX_PIX_CORR) &&
                       (FVID2_SOK == status)); idx++)
        {
            /* Write co-ordinates of defective pixels */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEM0);
            regVal &= ~ISIF_DFCMEM0_MASK;
            regVal |= ISIF_DFCMEM0_MASK & pVfdcCfg->defectivePixCoOr[0][idx];
            HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEM0, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEM1);
            regVal &= ~ISIF_DFCMEM1_MASK;
            regVal |= ISIF_DFCMEM1_MASK & pVfdcCfg->defectivePixCoOr[1][idx];
            HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEM1, regVal);

            /* Write defect values */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEM2);
            regVal &= ~ISIF_DFCMEM2_MASK;
            regVal |= ISIF_DFCMEM2_MASK & pVfdcCfg->subtractValues[0][idx];
            HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEM2, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEM3);
            regVal &= ~ISIF_DFCMEM3_MASK;
            regVal |= ISIF_DFCMEM3_MASK & pVfdcCfg->subtractValues[1][idx];
            HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEM3, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEM4);
            regVal &= ~ISIF_DFCMEM4_MASK;
            regVal |= ISIF_DFCMEM4_MASK & pVfdcCfg->subtractValues[2][idx];
            HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEM4, regVal);

            /* For the very first write, ensure internal memory table
                offset is cleared */
            if(0x0U == idx)
            {
                /* Enable internal memory write, with address tabel offset to
                    be reset */
                regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL);
                regVal |= ISIF_DFCMEMCTL_DFCMARST_MASK;
                regVal |= ISIF_DFCMEMCTL_DFCMWR_MASK;
                HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL, regVal);
            }
            else
            {
                regVal = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL);
                if(regVal & ISIF_DFCMEMCTL_DFCMARST_MASK)
                {
                    regVal &= ~ISIF_DFCMEMCTL_DFCMARST_MASK;
                    regVal |= ISIF_DFCMEMCTL_DFCMWR_MASK;
                    HW_WR_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL, regVal);
                }
            }

            /* Wait for internal memory write to complete */
            timeOut = ISS_HAL_ISIF_VFDC_MEM_TABLE_WRITE_WAIT;
            while((0U < timeOut) &&
                  (0U != (regVal & ISIF_DFCMEMCTL_DFCMWR_MASK)))
            {
                regVal = HW_RD_REG32(pInstObj->baseAddress + ISIF_DFCMEMCTL);
                timeOut--;
            }
            if(0x0U == timeOut)
            {
                status = FVID2_EFAIL;
            }
        }
    }
    else
    {
        status = FVID2_EFAIL;
    }

    return status;
}

/**  \brief Function to configure Optical Black Clamping sub-block.
            Perfroms NO error checks. Caller ensure all config is valid */
static int32_t IsifSetBlackClampConfig(
    const isshalisifInstObj_t          *pInstObj,
    const isshalisifBlackClampConfig_t *pBlkClampCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != pInstObj->baseAddress));

    if(NULL == pBlkClampCfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CLDCOFST);
        regVal &= ~ISIF_CLDCOFST_CLDC_MASK;
        regVal |= (pBlkClampCfg->dcOffset & ISIF_CLDCOFST_CLDC_MASK) <<
                  ISIF_CLDCOFST_CLDC_SHIFT;
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CLDCOFST, regVal);
    }

    return (status);
}

static int32_t IsifSetInFrmSize(
    const isshalisifInstObj_t   *pInstObj,
    const isshalisifSrcConfig_t *srcCfg)
{
    uint32_t regVal;

    if(((Int32)TRUE == Fvid2_isDataFmtYuv422(srcCfg->inDataFormat)) ||
       (FVID2_DF_YUV420SP_UV == srcCfg->inDataFormat))
    {
        regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_CCDCFG);
        regVal &= ~ISIF_CCDCFG_YCINSWP_MASK;
        if(TRUE == srcCfg->ycInSwap)
        {
            regVal |= ISIF_CCDCFG_YCINSWP_MASK;
        }
        HW_WR_REG32(pInstObj->baseAddress + ISIF_CCDCFG, regVal);
    }

    /* Set the HD/VD width and HD/VD Period */
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_HDW);
    regVal &= ~ISIF_HDW_MASK;
    regVal |= ((srcCfg->hdWidth - 1U) << ISIF_HDW_SHIFT) & ISIF_HDW_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_HDW, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDW);
    regVal &= ~ISIF_VDW_MASK;
    regVal |= ((srcCfg->vdWidth - 1U) << ISIF_VDW_SHIFT) & ISIF_VDW_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDW, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_PPLN);
    regVal &= ~ISIF_PPLN_MASK;
    regVal |= ((srcCfg->pixelsPerLine - 1U) << ISIF_PPLN_SHIFT) &
              ISIF_PPLN_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_PPLN, regVal);

    /* Set the HD Period */
    /* Sets number of half lines per frame or field.
     * VD period = (LPFR+1)/2 lines.*/
    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_LPFR);
    regVal &= ~ISIF_LPFR_MASK;
    regVal |= (((srcCfg->linesPerFrame * 2U) - 1U) << ISIF_LPFR_SHIFT) &
              ISIF_LPFR_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_LPFR, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDINT0);
    regVal &= ~ISIF_VDINT0_CVD0_MASK;
    regVal |= ((srcCfg->linesPerFrame - 1U) << ISIF_VDINT0_CVD0_SHIFT) &
              ISIF_VDINT0_CVD0_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDINT0, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDINT1);
    regVal &= ~ISIF_VDINT1_CVD1_MASK;
    regVal |= ((srcCfg->linesPerFrame - 1U) << ISIF_VDINT1_CVD1_SHIFT) &
              ISIF_VDINT1_CVD1_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDINT1, regVal);

    regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_VDINT2);
    regVal &= ~ISIF_VDINT2_CVD2_MASK;
    regVal |= ((srcCfg->linesPerFrame - 1U) << ISIF_VDINT2_CVD2_SHIFT) &
              ISIF_VDINT2_CVD2_MASK;
    HW_WR_REG32(pInstObj->baseAddress + ISIF_VDINT2, regVal);

    return (FVID2_SOK);
}

static int32_t IsifSet2DLscConfig(
    const isshalisifInstObj_t     *pInstObj,
    const vpsissIsif2DLscConfig_t *p2dLscCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != pInstObj));
    GT_assert(VpsHalTrace, (NULL != pInstObj->baseAddress));

    if(NULL == p2dLscCfg)
    {
        status = FVID2_EBADARGS;
    }

    if(FVID2_SOK == status)
    {
        if(TRUE == p2dLscCfg->enable)
        {
            /* Check for Errors */

            /* Start position must be less than down scale factor*/
            if((p2dLscCfg->startPos.startX >=
                ((uint32_t)1U << (uint32_t)p2dLscCfg->horzDownScale)) ||
               (p2dLscCfg->startPos.startY >=
                ((uint32_t)1U << (uint32_t)p2dLscCfg->vertDownScale)))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            /* Start position must be even */
            if((0U != (p2dLscCfg->startPos.startX % 2U)) ||
               (0U != (p2dLscCfg->startPos.startY % 2U)))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            /* Input Gain table address and offset must be 4 byte aligned */
            if((0U != (p2dLscCfg->gainTableAddr & 0x3U)) ||
               (0U != (p2dLscCfg->gainTablePitch & 0x3U)))
            {
                status = FVID2_EINVALID_PARAMS;
            }

            if(TRUE == p2dLscCfg->enableOffset)
            {
                /* Input offset table address and offset must be 4
                   byte aligned */
                if((0U != (p2dLscCfg->offsetTableAddr & 0x3U)) ||
                   (0U != (p2dLscCfg->offsetTablePitch & 0x3U)))
                {
                    status = FVID2_EINVALID_PARAMS;
                }
            }
        }
    }

    if(FVID2_SOK == status)
    {
        if(TRUE == p2dLscCfg->enable)
        {
            /* Set the Active Region */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_LSCHOFST);
            regVal &= ~ISIF_LSCHOFST_HOFST_MASK;
            regVal |= (p2dLscCfg->activeReg.cropStartX <<
                       ISIF_LSCHOFST_HOFST_SHIFT) &
                      ISIF_LSCHOFST_HOFST_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_LSCHOFST, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_LSCVOFST);
            regVal &= ~ISIF_LSCVOFST_VOFST_MASK;
            regVal |= (p2dLscCfg->activeReg.cropStartY <<
                       ISIF_LSCVOFST_VOFST_SHIFT) &
                      ISIF_LSCVOFST_VOFST_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_LSCVOFST, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_LSCHVAL);
            regVal &= ~ISIF_LSCHVAL_HVAL_MASK;
            regVal |= ((p2dLscCfg->activeReg.cropWidth - 1U) <<
                       ISIF_LSCHVAL_HVAL_SHIFT) &
                      ISIF_LSCHVAL_HVAL_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_LSCHVAL, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_LSCVVAL);
            regVal &= ~ISIF_LSCVVAL_VVAL_MASK;
            regVal |= ((p2dLscCfg->activeReg.cropHeight - 1U) <<
                       ISIF_LSCVVAL_VVAL_SHIFT) &
                      ISIF_LSCVVAL_VVAL_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_LSCVVAL, regVal);

            /* Configure the Start position */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCINI);
            regVal &= ~(ISIF_2DLSCINI_X_MASK | ISIF_2DLSCINI_Y_MASK);
            regVal |= (p2dLscCfg->startPos.startX << ISIF_2DLSCINI_X_SHIFT) &
                      ISIF_2DLSCINI_X_MASK;
            regVal |= (p2dLscCfg->startPos.startY << ISIF_2DLSCINI_Y_SHIFT) &
                      ISIF_2DLSCINI_Y_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCINI, regVal);

            /* Configure DownScaling factor and gain format */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCCFG);
            regVal &= ~(ISIF_2DLSCCFG_GAIN_FORMAT_MASK |
                        ISIF_2DLSCCFG_GAIN_MODE_N_MASK |
                        ISIF_2DLSCCFG_GAIN_MODE_M_MASK |
                        ISIF_2DLSCCFG_GAIN_RANGE_MASK);
            regVal |=
                (p2dLscCfg->gainFormat << ISIF_2DLSCCFG_GAIN_FORMAT_SHIFT) &
                ISIF_2DLSCCFG_GAIN_FORMAT_MASK;
            regVal |= (p2dLscCfg->horzDownScale <<
                       ISIF_2DLSCCFG_GAIN_MODE_M_SHIFT) &
                      ISIF_2DLSCCFG_GAIN_MODE_M_MASK;
            regVal |= (p2dLscCfg->vertDownScale <<
                       ISIF_2DLSCCFG_GAIN_MODE_N_SHIFT) &
                      ISIF_2DLSCCFG_GAIN_MODE_N_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCCFG, regVal);

            /* configure start address and offset for gain table */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCGRBU);
            regVal &= ~ISIF_2DLSCGRBU_BASE31_16_MASK;
            regVal |= ((p2dLscCfg->gainTableAddr >> 16U) <<
                       ISIF_2DLSCGRBU_BASE31_16_SHIFT) &
                      ISIF_2DLSCGRBU_BASE31_16_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCGRBU, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCGRBL);
            regVal &= ~ISIF_2DLSCGRBL_BASE15_0_MASK;
            regVal |= (p2dLscCfg->gainTableAddr <<
                       ISIF_2DLSCGRBL_BASE15_0_SHIFT) &
                      ISIF_2DLSCGRBL_BASE15_0_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCGRBL, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCGROF);
            regVal &= ~ISIF_2DLSCGROF_OFFSET_MASK;
            regVal |= (p2dLscCfg->gainTablePitch <<
                       ISIF_2DLSCGROF_OFFSET_SHIFT) &
                      ISIF_2DLSCGROF_OFFSET_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCGROF, regVal);

            /* configure start address and offset for offset table */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCORBU);
            regVal &= ~ISIF_2DLSCORBU_BASE_MASK;
            regVal |= ((p2dLscCfg->offsetTableAddr >> 16U) <<
                       ISIF_2DLSCORBU_BASE_SHIFT) &
                      ISIF_2DLSCORBU_BASE_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCORBU, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCORBL);
            regVal &= ~ISIF_2DLSCORBL_BASE_MASK;
            regVal |= (p2dLscCfg->offsetTableAddr <<
                       ISIF_2DLSCORBL_BASE_SHIFT) &
                      ISIF_2DLSCORBL_BASE_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCORBL, regVal);

            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCOROF);
            regVal &= ~ISIF_2DLSCOROF_OFFSET_MASK;
            regVal |= (p2dLscCfg->offsetTablePitch <<
                       ISIF_2DLSCOROF_OFFSET_SHIFT) &
                      ISIF_2DLSCOROF_OFFSET_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCOROF, regVal);

            /* Configure Scaling factor and shift up value for the offset */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCOFST);
            regVal &= ~(ISIF_2DLSCOFST_OFSTEN_MASK |
                        ISIF_2DLSCOFST_OFSTSF_MASK |
                        ISIF_2DLSCOFST_OFSTSFT_MASK);
            regVal |=
                (p2dLscCfg->offsetShiftup << ISIF_2DLSCOFST_OFSTSFT_SHIFT) &
                ISIF_2DLSCOFST_OFSTSFT_MASK;
            regVal |=
                (p2dLscCfg->offsetScaleFactor << ISIF_2DLSCOFST_OFSTSF_SHIFT) &
                ISIF_2DLSCOFST_OFSTSF_MASK;
            if(p2dLscCfg->enableOffset)
            {
                regVal |= ISIF_2DLSCOFST_OFSTEN_MASK;
            }
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCOFST, regVal);

            /* Enable after all configuration is done*/
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCCFG);
            regVal |= ISIF_2DLSCCFG_ENABLE_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCCFG, regVal);
        }
        else
        {
            /* Before disabling LSC,
               make sure that SOF event or Prefetch complete event is
               received, otherwise this may cause prefetch error event. */
            regVal  = HW_RD_REG32(pInstObj->baseAddress + ISIF_2DLSCCFG);
            regVal &= ~ISIF_2DLSCCFG_ENABLE_MASK;
            HW_WR_REG32(pInstObj->baseAddress + ISIF_2DLSCCFG, regVal);
        }
    }

    return (status);
}

