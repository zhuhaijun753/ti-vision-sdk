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
 * \file vps_resrcMgr.c
 *
 * \brief VPS Resource Manager Source file
 * This file exposes the APIs of the VPS Resource Manager.
 *
 *  \warning Following are the allocation policies followed.
 *      . CAL Resource allocation
 *          . All resources / instances are allocated starting from instance 0,
 *              exceptions are below.
 *          . DMA Write instance / channel allocation.
 *              0x0 is the least preferred channel, will allocate 1 to max,
 *              channel 0x0 would be allocated last
 *
 */

/* BUG TODO Sujith
 * Pixel Processing sub blocks cannot be allocated individually. Since there is
 *  1 cport ID for an instance of pix proc */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <osal/bsp_osal.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <common/vps_common.h>
#include <common/irm_resrcMgr.h>
#include <vps/iss/vps_isscommon.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CAL_MAX_PIX_PROC_CONTEXT        (0x4U)
/**< Maximum Pixel Processing context */
#define CAL_MAX_WR_DMA_CHANNEL          (0x8U)
/**< Maximum Pixel Processing context */
#define CAL_MAX_CPORT_ID                (0x8U)
/**< Maximum Pixel Processing context */
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Irm_CalInstObj
 *  \brief CAL Instance object.
 */
typedef struct Irm_CalInstObj
{
    UInt32 instId;
    /**< CAL Instance identifier. */
    UInt32 ppi;
    /**< PPI interface. TRUE is allocated, FALSE otherwise */
    UInt32 pixExtract[CAL_MAX_PIX_PROC_CONTEXT];
    /**< Pixel Extract */
    UInt32 dpmDecode[CAL_MAX_PIX_PROC_CONTEXT];
    /**< DPM Decode */
    UInt32 dpmEncode[CAL_MAX_PIX_PROC_CONTEXT];
    /**< DPM Encode */
    UInt32 pixPack[CAL_MAX_PIX_PROC_CONTEXT];
    /**< Pixel Pack */
    UInt32 bysOut;
    /**< BYS Out. TRUE is allocated, FALSE otherwise */
    UInt32 bysIn;
    /**< BYS IN. TRUE is allocated, FALSE otherwise */
    UInt32 vPort;
    /**< VPORT IN. TRUE is allocated, FALSE otherwise */
    UInt32 rdDma;
    /**< RD Dma. TRUE is allocated, FALSE otherwise */
    UInt32 wrDma[CAL_MAX_WR_DMA_CHANNEL];
    /**< WR Dma */
    UInt32 cport[CAL_MAX_CPORT_ID];
    /**< CPort */
    UInt32 csi2Ctx[CAL_MAX_CPORT_ID];
    /**< CSI2 Processing conext */
    UInt32 lvds;
    /**< LVDS port */
    UInt32 cpi;
    /**< Parallel / CPI interface */
} Irm_CaptInstObj_t;

/**
 *  struct Irm_InstObj
 *  \brief Resource object.
 */
typedef struct
{
    UInt32             isInited;
    /**< Flag to indicate if the its been initialized */
    UInt32             numCalInst;
    /**< Valid number of CAL instances */
    Irm_CaptInstObj_t *resCal[IRM_MAX_CAL_BLOCKS];
    /**< Capture Resources */
    BspOsal_SemHandle  lockSem;
    /**< Mutual exclusion */
} Irm_InstObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  allocCaptRes
 *  \brief Function to allocate resource from instannce of CAL.
 */
static Int32 allocCaptRes(Irm_CaptInstObj_t *pAvailRes, UInt32 reqRes,
                          vpsissCaptureBlocks_t *pAllocRes, UInt32 flags);

/**
 *  releaseCaptRes
 *  \brief Function to allocate resource from instannce of CAL.
 */
static Int32 releaseCaptRes(Irm_CaptInstObj_t           *pAvailRes,
                            const vpsissCaptureBlocks_t *pAllocRes);
/* ========================================================================== */
/*                        Global Variables                                    */
/* ========================================================================== */

/** \brief Resource object. */
/* Require to initialize isInited flag alone Not much worried about others */
static Irm_InstObj_t gIrmInstObj = {FALSE, 0x0, {NULL, NULL}, NULL};

/** \brief CAL Resource object. */
Irm_CaptInstObj_t    gIrmCalObjs[IRM_MAX_CAL_BLOCKS];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Irm_init
 *  \brief Function to initialize Resource manager.
 */
Int32 Irm_init(UInt32 numInst, const Irm_InitParams_t *instPrms)
{
    UInt32 i;
    Int32  retVal = BSP_EBADARGS;

    /* Args checks */
    if (NULL != instPrms)
    {
        if (instPrms->numCalBlocks <= IRM_MAX_CAL_BLOCKS)
        {
            retVal = BSP_SOK;
        }
    }

    if ((FALSE == gIrmInstObj.isInited) && (BSP_SOK == retVal))
    {
        /* Init objects and mark flags as free */
        BspUtils_memset((Ptr) & gIrmInstObj, 0U, sizeof (Irm_InstObj_t));
        for (i = 0; i < IRM_MAX_CAL_BLOCKS; i++)
        {
            gIrmInstObj.resCal[i] = &gIrmCalObjs[i];
            /* Initialize all the resources */
            BspUtils_memset((Ptr) (&gIrmCalObjs[i]), 0U,
                            sizeof (Irm_CaptInstObj_t));
            gIrmCalObjs[i].instId = i;
        }

        /* Get the semaphore handle */
        gIrmInstObj.lockSem = BspOsal_semCreate((int32_t) 1, TRUE);
        if (NULL == gIrmInstObj.lockSem)
        {
            retVal = BSP_EALLOC;
/* MISRA.UNREACH.GEN
 * Un Reachable code
 * Name 'retVal = BSP_EALLOC;'
 * KW State: Not A Problem -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable
 */
        }

        if (BSP_SOK == retVal)
        {
            gIrmInstObj.isInited = (uint32_t) TRUE;
        }
    }

    return (retVal);
}

/**
 *  Vrm_deInit
 *  \brief Function to de-initialize the resource manager.
 */
Int32 Irm_deInit(void)
{
    Int32  rtnVal = BSP_SOK;
    Irm_CaptInstObj_t *pAvailRes;
    UInt32 i, j;

    if (TRUE == gIrmInstObj.isInited)
    {
        for (i = 0; ((BSP_SOK == rtnVal) && (i < IRM_MAX_CAL_BLOCKS)); i++)
        {
            pAvailRes = gIrmInstObj.resCal[i];
            if (pAvailRes != NULL)
            {
                if ((pAvailRes->ppi != FALSE) || (pAvailRes->bysOut != FALSE))
                {
                    rtnVal = BSP_EDEVICE_INUSE;
                }
                else if ((pAvailRes->bysIn != FALSE) ||
                         (pAvailRes->vPort != FALSE))
                {
                    rtnVal = BSP_EDEVICE_INUSE;
                }
                else if (pAvailRes->rdDma != FALSE)
                {
                    rtnVal = BSP_EDEVICE_INUSE;
                }
                else
                {
                    /* Nothing to be done here */
                }

                if (rtnVal == BSP_EDEVICE_INUSE)
                {
                    break;
                }

                for (j = 0; j < CAL_MAX_PIX_PROC_CONTEXT; j++)
                {
                    if ((pAvailRes->pixExtract[j] != FALSE) ||
                        (pAvailRes->dpmDecode[j] != FALSE) ||
                        (pAvailRes->dpmEncode[j] != FALSE) ||
                        (pAvailRes->pixPack[j] != FALSE))
                    {
                        rtnVal = BSP_EDEVICE_INUSE;
                        break;
                    }
                }

                for (j = 0; j < CAL_MAX_WR_DMA_CHANNEL; j++)
                {
                    if (pAvailRes->wrDma[j] != FALSE)
                    {
                        rtnVal = BSP_EDEVICE_INUSE;
                        break;
                    }
                }
                for (j = 0; j < CAL_MAX_CPORT_ID; j++)
                {
                    if (pAvailRes->cport[j] != FALSE)
                    {
                        rtnVal = BSP_EDEVICE_INUSE;
                        break;
                    }
                }
                for (j = 0; j < CAL_MAX_WR_DMA_CHANNEL; j++)
                {
                    if (pAvailRes->csi2Ctx[j] != FALSE)
                    {
                        rtnVal = BSP_EDEVICE_INUSE;
                        break;
                    }
                }
            }
            else
            {
                rtnVal = BSP_EBADARGS;
            }
        }
        if (BSP_SOK == rtnVal)
        {
            BspOsal_semDelete(&(gIrmInstObj.lockSem));
            BspUtils_memset((Ptr) & gIrmInstObj, 0, sizeof (Irm_InstObj_t));
        }
    }

    return (BSP_SOK);
}

Int32 Irm_allocResource(UInt32 instId, Irm_Modules_t module,
                        UInt32 reqRes, Ptr allocRes, UInt32 flags)
{
    Int32 rtnVal = BSP_EBADARGS;
    if ((TRUE == gIrmInstObj.isInited) && (NULL != allocRes))
    {
        if ((IRM_MODULE_CAL_A == module) || (IRM_MODULE_CAL_B == module))
        {
            BspOsal_semWait(gIrmInstObj.lockSem, BSP_OSAL_WAIT_FOREVER);
            rtnVal = allocCaptRes(gIrmInstObj.resCal[module], reqRes,
                                  (vpsissCaptureBlocks_t *) allocRes, flags);
            BspOsal_semPost(gIrmInstObj.lockSem);
        }
    }
    return rtnVal;
}

Int32 Irm_releaseResource(UInt32 instId, Irm_Modules_t module,
                          Ptr relRes)
{
    Int32 rtnVal = BSP_EBADARGS;
    if ((TRUE == gIrmInstObj.isInited) && (NULL != relRes))
    {
        if ((IRM_MODULE_CAL_A == module) || (IRM_MODULE_CAL_B == module))
        {
            BspOsal_semWait(gIrmInstObj.lockSem, BSP_OSAL_WAIT_FOREVER);
            rtnVal = releaseCaptRes(gIrmInstObj.resCal[module],
                                    (vpsissCaptureBlocks_t *) relRes);
            BspOsal_semPost(gIrmInstObj.lockSem);
        }
    }
    return rtnVal;
}

/* ========================================================================== */
/*                        Local Function Definitions                          */
/* ========================================================================== */

static Int32 allocCaptRes(Irm_CaptInstObj_t *pAvailRes, UInt32 reqRes,
                          vpsissCaptureBlocks_t *pAllocRes, UInt32 flags)
{
    UInt32 i;
    Int32  rtnVal = BSP_SOK;
    if ((NULL == pAllocRes) || (NULL == pAvailRes))
    {
        rtnVal = BSP_EBADARGS;
    }
    else
    {
        BspUtils_memset((Ptr) pAllocRes, (UInt8) 0xFF,
                        sizeof (vpsissCaptureBlocks_t));
    }
    if (BSP_SOK == rtnVal)
    {
        if (VPS_ISS_CAPT_CAL_SUB_PPI_ID ==
            (reqRes & VPS_ISS_CAPT_CAL_SUB_PPI_ID))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_PPI_ID;
            if (FALSE == pAvailRes->ppi)
            {
                pAvailRes->ppi = (uint32_t) TRUE;
                pAllocRes->ppi = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID;
            rtnVal  = BSP_EALLOC;
            for (i = 0; i < CAL_MAX_PIX_PROC_CONTEXT; i++)
            {
                if (FALSE == pAvailRes->pixExtract[i])
                {
                    pAvailRes->pixExtract[i] = (uint32_t) TRUE;
                    pAllocRes->pixExtract    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_DPCM_DEC_ID;
            rtnVal  = BSP_EALLOC;
            for (i = 0; i < CAL_MAX_PIX_PROC_CONTEXT; i++)
            {
                if (FALSE == pAvailRes->dpmDecode[i])
                {
                    pAvailRes->dpmDecode[i] = (uint32_t) TRUE;
                    pAllocRes->dpmDecode    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_DPCM_ENC_ID;
            rtnVal  = BSP_EALLOC;
            for (i = 0; i < CAL_MAX_PIX_PROC_CONTEXT; i++)
            {
                if (FALSE == pAvailRes->dpmEncode[i])
                {
                    pAvailRes->dpmEncode[i] = (uint32_t) TRUE;
                    pAllocRes->dpmEncode    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_PIX_PACK_ID;
            rtnVal  = BSP_EALLOC;
            for (i = 0; i < CAL_MAX_PIX_PROC_CONTEXT; i++)
            {
                if (FALSE == pAvailRes->pixPack[i])
                {
                    pAvailRes->pixPack[i] = (uint32_t) TRUE;
                    pAllocRes->pixPack    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_BYS_OUT_ID;
            if (FALSE == pAvailRes->bysOut)
            {
                pAvailRes->bysOut = (uint32_t) TRUE;
                pAllocRes->bysOut = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_BYS_IN_ID;
            if (FALSE == pAvailRes->bysIn)
            {
                pAvailRes->bysIn = (uint32_t) TRUE;
                pAllocRes->bysIn = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_VPORT_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_VPORT_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_VPORT_ID;
            if (FALSE == pAvailRes->vPort)
            {
                pAvailRes->vPort = (uint32_t) TRUE;
                pAllocRes->vPort = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_DMA_RD_ID;
            if (FALSE == pAvailRes->rdDma)
            {
                pAvailRes->rdDma = (uint32_t) TRUE;
                pAllocRes->rdDma = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        /* CPORT Allocation should be before WR DMA allocation, as based on DMA
         *  type, the allocation policy changes. */

        if ((VPS_ISS_CAPT_CAL_SUB_CPORT_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_CPORT_ID)) &&
            (BSP_SOK == rtnVal))
        {
            UInt32 cportIdStart = 1U;

            /* Check for cport allocation policies */
            if (IRM_CAL_ALLOC_POLICY_CPORTID_0_LEAST_PREFFERED !=
                (IRM_CAL_ALLOC_POLICY_CPORTID_0_LEAST_PREFFERED & flags))
            {
                cportIdStart = 0;
            }

            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_CPORT_ID;
            rtnVal  = BSP_EALLOC;
            for (i = cportIdStart; i < CAL_MAX_CPORT_ID; i++)
            {
                if (FALSE == pAvailRes->cport[i])
                {
                    pAvailRes->cport[i] = (uint32_t) TRUE;
                    pAllocRes->cport    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }
            if ((BSP_EALLOC == rtnVal) && (1U == cportIdStart))
            {
                if (FALSE == pAvailRes->cport[0])
                {
                    pAvailRes->cport[i] = (uint32_t) TRUE;
                    pAllocRes->cport    = i;
                    rtnVal = BSP_SOK;
                }
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_DMA_WR_ID;
            rtnVal  = BSP_EALLOC;

            /* Policy - write channel 0x0, is least preferred. Reserve it for
             *  last */
            i = 1U;
            if (IRM_CAL_ALLOC_POLICY_WRDMA_0_LEAST_PREFFERED !=
                (IRM_CAL_ALLOC_POLICY_WRDMA_0_LEAST_PREFFERED & flags))
            {
                i = 0;
            }

            for (; i < CAL_MAX_WR_DMA_CHANNEL; i++)
            {
                if (FALSE == pAvailRes->wrDma[i])
                {
                    pAvailRes->wrDma[i] = (uint32_t) TRUE;
                    pAllocRes->wrDma    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }

            if (BSP_EALLOC == rtnVal)
            {
                if (FALSE == pAvailRes->wrDma[0x0U])
                {
                    pAvailRes->wrDma[0x0U] = (uint32_t) TRUE;
                    pAllocRes->wrDma       = 0x0U;
                    rtnVal = BSP_SOK;
                }
            }
        }

        if ((VPS_ISS_CAPT_CAL_SUB_CSI2_ID ==
             (reqRes & VPS_ISS_CAPT_CAL_SUB_CSI2_ID)) &&
            (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CAL_SUB_CSI2_ID;
            rtnVal  = BSP_EALLOC;
            for (i = 0; i < CAL_MAX_CPORT_ID; i++)
            {
                if (FALSE == pAvailRes->csi2Ctx[i])
                {
                    pAvailRes->csi2Ctx[i] = (uint32_t) TRUE;
                    pAllocRes->csi2Ctx    = i;
                    rtnVal = BSP_SOK;
                    break;
                }
            }
        }

        if ((VPS_ISS_CAPT_LVDS_ID ==
             (reqRes & VPS_ISS_CAPT_LVDS_ID)) && (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_LVDS_ID;
            if (FALSE == pAvailRes->lvds)
            {
                pAvailRes->lvds = (uint32_t) TRUE;
                pAllocRes->lvds = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        if ((VPS_ISS_CAPT_CPI_ID ==
             (reqRes & VPS_ISS_CAPT_CPI_ID)) && (BSP_SOK == rtnVal))
        {
            reqRes &= ~VPS_ISS_CAPT_CPI_ID;
            if (FALSE == pAvailRes->cpi)
            {
                pAvailRes->cpi = (uint32_t) TRUE;
                pAllocRes->cpi = 0x0;
            }
            else
            {
                rtnVal = BSP_EALLOC;
            }
        }

        if (BSP_SOK != rtnVal)
        {
            /* TODO release acquired resources */
            rtnVal = BSP_EBADARGS;
        }
    }

    return rtnVal;
}

static Int32 releaseCaptRes(Irm_CaptInstObj_t           *pAvailRes,
                            const vpsissCaptureBlocks_t *pAllocRes)
{
    Int32 rtnVal = BSP_SOK;
    if ((NULL == pAllocRes) || (NULL == pAvailRes))
    {
        rtnVal = BSP_EBADARGS;
    }

    if (BSP_SOK == rtnVal)
    {
        if (0xFFFFFFFFU != pAllocRes->ppi)
        {
            pAvailRes->ppi = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->pixExtract) &&
            (CAL_MAX_PIX_PROC_CONTEXT > pAllocRes->pixExtract))
        {
            pAvailRes->pixExtract[pAllocRes->pixExtract] = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->dpmDecode) &&
            (CAL_MAX_PIX_PROC_CONTEXT > pAllocRes->dpmDecode))
        {
            pAvailRes->dpmDecode[pAllocRes->dpmDecode] = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->dpmEncode) &&
            (CAL_MAX_PIX_PROC_CONTEXT > pAllocRes->dpmEncode))
        {
            pAvailRes->dpmEncode[pAllocRes->dpmEncode] = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->pixPack) &&
            (CAL_MAX_PIX_PROC_CONTEXT > pAllocRes->pixPack))
        {
            pAvailRes->pixPack[pAllocRes->pixPack] = (uint32_t) FALSE;
        }
        if (0xFFFFFFFFU != pAllocRes->bysOut)
        {
            pAvailRes->bysOut = (uint32_t) FALSE;
        }
        if (0xFFFFFFFFU != pAllocRes->bysIn)
        {
            pAvailRes->bysIn = (uint32_t) FALSE;
        }
        if (0xFFFFFFFFU != pAllocRes->vPort)
        {
            pAvailRes->vPort = (uint32_t) FALSE;
        }
        if (0xFFFFFFFFU != pAllocRes->rdDma)
        {
            pAvailRes->rdDma = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->wrDma) &&
            (CAL_MAX_WR_DMA_CHANNEL > pAllocRes->wrDma))
        {
            pAvailRes->wrDma[pAllocRes->wrDma] = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->cport) &&
            (CAL_MAX_CPORT_ID > pAllocRes->cport))
        {
            pAvailRes->cport[pAllocRes->cport] = (uint32_t) FALSE;
        }
        if (0xFFFFFFFFU != pAllocRes->lvds)
        {
            pAvailRes->lvds = (uint32_t) FALSE;
        }
        if (0xFFFFFFFFU != pAllocRes->cpi)
        {
            pAvailRes->cpi = (uint32_t) FALSE;
        }
        if ((0xFFFFFFFFU != pAllocRes->csi2Ctx) &&
            (CAL_MAX_CPORT_ID > pAllocRes->csi2Ctx))
        {
            pAvailRes->csi2Ctx[pAllocRes->csi2Ctx] = (uint32_t) FALSE;
        }
    }
    return rtnVal;
}

