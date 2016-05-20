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
 *  \file bsputils_mem.c
 *
 *  \brief Frame buffer memory allocator API.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/knl/Clock.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <vps/vps.h>
#include <bsputils_mem.h>

/* See bsputils_mem.h for function documentation  */

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

/* Memory pool handle */
HeapMem_Handle gBspUtils_heapMemFrameHandle = NULL;
HeapMem_Struct gBspUtils_heapMemFrameStruct;

Bool           gBspUtils_memClearBuf;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 BspUtils_memInit_internal(UInt32 *pMemAddr, UInt32 memSize)
{
    HeapMem_Params heapMemPrm;

    /* create memory pool heap  */
    HeapMem_Params_init(&heapMemPrm);

    heapMemPrm.buf  = pMemAddr;
    heapMemPrm.size = memSize;

    HeapMem_construct(&gBspUtils_heapMemFrameStruct, &heapMemPrm);
    gBspUtils_heapMemFrameHandle = HeapMem_handle(&gBspUtils_heapMemFrameStruct);
    GT_assert(BspAppTrace, gBspUtils_heapMemFrameHandle != NULL);

    gBspUtils_memClearBuf = (Bool) FALSE;

    return (BSP_SOK);
}

Int32 BspUtils_memDeInit(void)
{
    /* delete memory pool heap  */
    HeapMem_destruct(&gBspUtils_heapMemFrameStruct);
    gBspUtils_heapMemFrameHandle = NULL;

    return (BSP_SOK);
}

Int32 BspUtils_memFrameGetSize(const Fvid2_Format *pFormat,
                               UInt32             *size,
                               UInt32             *cOffset)
{
    Int32  status = BSP_SOK;
    UInt32 bufferHeight;

    bufferHeight = pFormat->height;
    switch (pFormat->dataFormat)
    {
        case FVID2_DF_RAW08:
        case FVID2_DF_RAW16:
        case FVID2_DF_RAW24:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV444I:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_BGR24_888:
        case FVID2_DF_RAW_VBI:
        case FVID2_DF_BGRX_4444:
        case FVID2_DF_XBGR_4444:
        case FVID2_DF_AGBR16_4444:
        case FVID2_DF_RGBA16_4444:
        case FVID2_DF_XGBR16_1555:
        case FVID2_DF_AGBR16_1555:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_XBGR24_8888:
        case FVID2_DF_RGBX24_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_BAYER_RAW:
        case FVID2_DF_BAYER_GRBG:
        case FVID2_DF_BAYER_RGGB:
        case FVID2_DF_BAYER_BGGR:
        case FVID2_DF_BAYER_GBRG:
            /* for single plane data format's */
            *size = pFormat->pitch[0] * bufferHeight;
            break;

        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV420SP_UV:
            /* for Y plane  */
            *size = pFormat->pitch[0] * bufferHeight;

            /* cOffset is at end of Y plane  */
            if (NULL != cOffset)
            {
                *cOffset = *size;
            }
            if (pFormat->dataFormat == FVID2_DF_YUV420SP_UV)
            {
                /* C plane height is 1/2 of Y plane */
                bufferHeight = bufferHeight / 2U;
            }

            /* for C plane  */
            *size += (pFormat->pitch[1] * bufferHeight);
            break;

        default:
            /* illegal data format  */
            status = BSP_EFAIL;
            break;
    }

    /* align size to minimum required frame buffer alignment  */
    *size = VpsUtils_align(*size, (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);

    return (status);
}

Int32 BspUtils_memFrameAlloc(Fvid2_Format *pFormat,
                             Fvid2_Frame  *pFrame,
                             UInt32        numFrames)
{
    Int32  status;
    UInt32 size, cOffset, frameId;
    UInt8 *pBaseAddr;

    /* align height to multiple of 2  */
    pFormat->height = VpsUtils_align(pFormat->height, (UInt32) 2U);

    /* get frame size for given pFormat */
    status = BspUtils_memFrameGetSize(pFormat, &size, &cOffset);
    if (status == BSP_SOK)
    {
        /* allocate the memory for 'numFrames' */

        /* for all 'numFrames' memory is contigously allocated  */
        pBaseAddr = (UInt8 *) BspUtils_memAlloc(
            (size * numFrames),
            (UInt32) VPS_BUFFER_ALIGNMENT_RECOMMENDED);
        if (pBaseAddr == NULL)
        {
            status = BSP_EALLOC;  /* Error in allocation, exit with error */
        }
    }

    if (status == BSP_SOK)
    {
        /* init memory pointer for 'numFrames'  */
        for (frameId = 0; frameId < numFrames; frameId++)
        {
            /* init Fvid2_Frame to 0's  */
            Fvid2Frame_init(pFrame);

            /* copy chNum to Fvid2_Frame from Fvid2_Format */
            pFrame->chNum      = pFormat->chNum;
            pFrame->addr[0][0] = pBaseAddr;

            switch (pFormat->dataFormat)
            {
                case FVID2_DF_RAW08:
                case FVID2_DF_RAW16:
                case FVID2_DF_RAW24:
                case FVID2_DF_RAW_VBI:
                case FVID2_DF_YUV422I_UYVY:
                case FVID2_DF_YUV422I_VYUY:
                case FVID2_DF_YUV422I_YUYV:
                case FVID2_DF_YUV422I_YVYU:
                case FVID2_DF_YUV444I:
                case FVID2_DF_RGB24_888:
                case FVID2_DF_BGR24_888:
                case FVID2_DF_BGRX_4444:
                case FVID2_DF_XBGR_4444:
                case FVID2_DF_AGBR16_4444:
                case FVID2_DF_RGBA16_4444:
                case FVID2_DF_XGBR16_1555:
                case FVID2_DF_AGBR16_1555:
                case FVID2_DF_BGR16_565:
                case FVID2_DF_XBGR24_8888:
                case FVID2_DF_RGBX24_8888:
                case FVID2_DF_ARGB32_8888:
                case FVID2_DF_ABGR32_8888:
                case FVID2_DF_RGBA32_8888:
                case FVID2_DF_BGRA32_8888:
                case FVID2_DF_BAYER_RAW:
                case FVID2_DF_BAYER_GRBG:
                case FVID2_DF_BAYER_RGGB:
                case FVID2_DF_BAYER_BGGR:
                case FVID2_DF_BAYER_GBRG:
                    break;
                case FVID2_DF_YUV422SP_UV:
                case FVID2_DF_YUV420SP_UV:
                    /* assign pointer for C plane */
                    pFrame->addr[0][1] = (UInt8 *) pFrame->addr[0][0] + cOffset;
                    break;
                default:
                    /* illegal data format  */
                    status = BSP_EFAIL;
                    break;
            }

            /* go to next frame */
            pFrame++;
            /* increment base address */
            pBaseAddr += size;
        }
    }

    GT_assert(BspAppTrace, status == BSP_SOK);

    return (status);
}

Int32 BspUtils_memFrameFree(const Fvid2_Format *pFormat,
                            Fvid2_Frame        *pFrame,
                            UInt32              numFrames)
{
    Int32  status;
    UInt32 size, cOffset;

    /* get frame size for given 'pFormat' */
    status = BspUtils_memFrameGetSize(pFormat, &size, &cOffset);
    if (status == BSP_SOK)
    {
        /* free the frame buffer memory */

        /* for all 'numFrames' memory is allocated contigously during alloc,
         *  so first frame memory pointer points to the complete
         *  memory block for all frames */
        BspUtils_memFree(pFrame->addr[0][0], (size * numFrames));
    }

    return (BSP_SOK);
}

Ptr BspUtils_memAlloc(UInt32 size, UInt32 align)
{
    Ptr addr;

    /* allocate memory  */
    addr = HeapMem_alloc(gBspUtils_heapMemFrameHandle, size, align, NULL);
    if (((Bool) (addr != NULL)) && gBspUtils_memClearBuf)
    {
        BspUtils_memset(addr, 0x80U, size);
    }

    return (addr);
}

Int32 BspUtils_memFree(Ptr addr, UInt32 size)
{
    /* free previously allocated memory  */
    HeapMem_free(gBspUtils_heapMemFrameHandle, addr, size);

    return (BSP_SOK);
}

Int32 BspUtils_memClearOnAlloc(Bool enable)
{
    gBspUtils_memClearBuf = enable;

    return (BSP_SOK);
}

/**
 *  BspUtils_memGetHeapStat
 *  \brief Returns the current status (free size) of the various heaps used.
 *
 *  \param heapStat [OUT]   Status filled by the function.
 *
 */
void BspUtils_memGetHeapStat(BspUtils_MemHeapStatus *heapStat)
{
    /* NULL pointer check */
    GT_assert(BspAppTrace, NULL != heapStat);

    heapStat->freeSysHeapSize  = BspUtils_memGetSystemHeapFreeSpace();
    heapStat->freeBufHeapSize  = BspUtils_memGetBufferHeapFreeSpace();

    return;
}

/**
 *  BspUtils_memCheckHeapStat
 *  \brief Checks the current status of each heap with the value passed.
 *  This returns an error if the values of each of the heap doesn't match.
 *
 *  \param heapStat [IN]    Older status to be compared with the current status.
 *
 *  \return                 Returns 0 if the heap sizes match else return
 *                          BSP_EFAIL.
 */
Int32 BspUtils_memCheckHeapStat(const BspUtils_MemHeapStatus *heapStat)
{
    Int32 retVal = BSP_SOK;
    BspUtils_MemHeapStatus curStat;

    /* NULL pointer check */
    GT_assert(BspAppTrace, NULL != heapStat);

    BspUtils_memGetHeapStat(&curStat);

    if (heapStat->freeSysHeapSize != curStat.freeSysHeapSize)
    {
        GT_1trace(BspAppTrace, GT_CRIT,
                  "Warning: Memory leak (%d bytes) in System Heap!!\n",
                  (heapStat->freeSysHeapSize - curStat.freeSysHeapSize));
        retVal = BSP_EFAIL;
    }
    if (heapStat->freeBufHeapSize != curStat.freeBufHeapSize)
    {
        GT_1trace(BspAppTrace, GT_CRIT,
                  "Warning: Memory leak (%d bytes) in Buffer Heap!!\n",
                  (heapStat->freeBufHeapSize - curStat.freeBufHeapSize));
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

UInt32 BspUtils_memGetSystemHeapFreeSpace(void)
{
    Memory_Stats stats;
    extern const IHeap_Handle Memory_defaultHeapInstance;

    Memory_getStats(Memory_defaultHeapInstance, &stats);

    return ((UInt32) (stats.totalFreeSize));
}

UInt32 BspUtils_memGetBufferHeapFreeSpace(void)
{
    UInt32       totalFreeSize = 0U;
    Memory_Stats stats;

    if (NULL != gBspUtils_heapMemFrameHandle)
    {
        HeapMem_getStats(gBspUtils_heapMemFrameHandle, &stats);
        totalFreeSize = (UInt32) stats.totalFreeSize;
    }

    return (totalFreeSize);
}

